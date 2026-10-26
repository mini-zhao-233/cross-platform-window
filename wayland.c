#include <stdint.h>
#include <stdio.h>
#include <wayland-client-core.h>
#include <wayland-client.h>
#include <wayland-client-protocol.h>

/*
 * static declaration
 */

static void on_global_added(void* data, struct wl_registry* wl_registry, uint32_t name, const char* interface, uint32_t version);

static void on_global_removed(void* data, struct wl_registry* wl_registry, uint32_t name);

/*
 *  static variables
 */
static struct wl_registry_listener s_registry_listener = {
  .global = on_global_added,
  .global_remove = on_global_removed
};

int main(void){
  struct wl_display* disp = wl_display_connect(NULL);
  if (!disp){
    return 1;
  }

  struct wl_registry* reg = wl_display_get_registry(disp);
  if(!disp){
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
 static void on_global_added(void* data, struct wl_registry* wl_registry, uint32_t name, const char* interface, uint32_t version){
   fprintf(stderr, "Global added: %s, v %d (name %d)\n", interface, version, name);
 }

 static void on_global_removed(void* data, struct wl_registry* wl_registry, uint32_t name){
   fprintf(stderr, "Global removed: name: %d\n", name);
 }
