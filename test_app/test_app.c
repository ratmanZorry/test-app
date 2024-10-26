#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>

// Define scene names
typedef enum {
    SceneA,
    SceneB,
} AppScene;

// Application state with current scene
typedef struct {
    AppScene current_scene;
} AppState;

// Render callback for displaying scenes
static void render_callback(Canvas* canvas, void* context) {
    AppState* app_state = (AppState*)context;
    canvas_clear(canvas);

    if(app_state->current_scene == SceneA) {
        canvas_draw_str(canvas, 10, 10, "Scene A");
    } else if(app_state->current_scene == SceneB) {
        canvas_draw_str(canvas, 10, 10, "Scene B");
    }
}

// Input callback for switching scenes
static void input_callback(InputEvent* input_event, void* context) {
    AppState* app_state = (AppState*)context;

    if(input_event->type == InputTypeShort && input_event->key == InputKeyOk) {
        // Toggle between scenes
        app_state->current_scene = (app_state->current_scene == SceneA) ? SceneB : SceneA;
    }
}

int32_t test_app_app(void) {
    AppState app_state = { .current_scene = SceneA }; // Start with Scene A

    // Set up the viewport and GUI
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, render_callback, &app_state);
    view_port_input_callback_set(view_port, input_callback, &app_state);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    // Main loop
    while(1) {
        view_port_update(view_port); 
        furi_delay_ms(100);          
    }


    view_port_enabled_set(view_port, false);
    gui_remove_view_port(gui, view_port);
    furi_record_close(RECORD_GUI);
    view_port_free(view_port);

    return 0;
}
