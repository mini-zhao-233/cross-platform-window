#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

/*
 * static declaration
 */

static void on_global_added(void *data, struct wl_registry *wl_registry,
                            uint32_t name, const char *interface,
                            uint32_t version);

static void on_global_removed(void *data, struct wl_registry *wl_registry,
                              uint32_t name);

static void global_registry_handler(void *data, struct wl_registry *wl_registry,
                                    uint32_t id, const char *interface,
                                    uint32_t version);

static void shm_format(void *data, struct wl_shm *wl_shm, uint32_t format);

static struct wl_buffer* create_buffer();
  
static void create_window();
/*
 *  static variables
 */
static int WIDTH = 480;
static int HEIGHT = 360;

static const struct wl_registry_listener s_registry_listener = {
    .global = global_registry_handler, .global_remove = on_global_removed};

static struct wl_compositor *compositor = NULL;

struct wl_shm *shm = NULL;

struct wl_shm_listener shm_listener = {
    .format = shm_format,
};

struct wl_buffer* buffer = NULL;
struct wl_surface* surface = NULL;

void* shm_data;

int main(void) {
  struct wl_display *disp = wl_display_connect(NULL);
  if (!disp) {
    return 1;
  }

  struct wl_registry *reg = wl_display_get_registry(disp);
  if (!disp) {
    return 1;
  }

  wl_registry_add_listener(reg, &s_registry_listener, NULL);

  wl_display_dispatch(disp);
  wl_display_roundtrip(disp);

  printf("nothing to display");

  wl_registry_destroy(reg);
  wl_display_disconnect(disp);

  return 0;
}

/*
 *
 */
static void on_global_added(void *data, struct wl_registry *wl_registry,
                            uint32_t name, const char *interface,
                            uint32_t version) {
  fprintf(stderr, "Global added: %s, v %d (name %d)\n", interface, version,
          name);
}

static void on_global_removed(void *data, struct wl_registry *wl_registry,
                              uint32_t name) {
  fprintf(stderr, "Global removed: name: %d\n", name);
}

static void shm_format(void *data, struct wl_shm *wl_shm, uint32_t format) {
  fprintf(stderr,"Format %d\n",format);
}

static void global_registry_handler(void *data, struct wl_registry *wl_registry,
                                    uint32_t id, const char *interface,
                                    uint32_t version) {
  printf("Got a registry event for %s id %d\n", interface, id);

  if (strcmp(interface, "wl_compositor") == 0) {
    compositor =
        wl_registry_bind(wl_registry, id, &wl_compositor_interface, version);

  } else if (strcmp(interface, "wl_shm") == 0) {
    shm = wl_registry_bind(wl_registry, id, &wl_shm_interface, version);
    wl_shm_add_listener(shm, &shm_listener, NULL);
  }
}

static struct wl_buffer* create_buffer(){
  struct wl_shm_pool* pool;
  int stride = WIDTH * 4;
  int size = stride * HEIGHT;
  int fd;
  struct wl_buffer *buff;

  fd = os_create_anonymous_file(size);

  if (fd<0){
    return NULL;
  }

  shm_data = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if (shm_data == MAP_FAILED) {
    close(fd);
    return NULL;
  }
  pool = wl_shm_create_pool(shm, fd, size);
  buff = wl_shm_pool_create_buffer(pool, 0, WIDTH, HEIGHT, stride, WL_SHM_FORMAT_XRGB8888);
  wl_shm_pool_destroy(pool);
  return buff;
}

static void create_window(){
  buffer = create_buffer();
  wl_surface_attach(surface, buffer, 0, 0);
  wl_surface_commit(surface);
}
