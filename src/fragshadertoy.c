#include "components/button.h"
#include "constants.h"
#include "raylib.h"
#include "stb_ds.h"
#include "util.h"
#include "fragshadertoy.h"

// c23 embed directive allows placing data into source directly
// doesn't null terminate so suffix(, 0) is needed afterwards (or , 0 on new line)
// to make it a proper string
static const char FRAG_PIXELISER[] = {
#embed "shaders/pixeliser.fsh" suffix(, 0)
};
static const char FRAG_TORCH[] = {
#embed "shaders/torch.fsh" suffix(, 0)
};

typedef struct {
    bool showGuide;
    bool killed;  // stop updates so everything can unload
    int currentShader;
    Camera2D camera;
} State;

const int WORLD_WIDTH = 1600;
const int WORLD_HEIGHT = 1000;

static State state; 

static SimpleText guide = {
    20, 20, 20, WHITE, 
    "FRAG SHADER TOY - [esc] to exit [h] to hide\n"
    "[1] Default shader\n"
    "[2] Pixel shader\n"
    "[3] Torch shader"
};

static Shader* shaders;
static int torchShaderMouseLoc;
static int torchShaderResolutionLoc;

static Texture2D prettyPicture;
static Rectangle prettyPicture_rect;
static RenderTexture2D renderTarget;

void FragShaderToy_init() {
    state = (State){
        true,
        false,
        0,
        initialiseScaledCamera(WORLD_WIDTH, WORLD_HEIGHT)
    };
    prettyPicture = LoadTexture("assets/textures/hills-1-crop.png");
    prettyPicture_rect = (Rectangle){0, 0, prettyPicture.width, prettyPicture.height};
    renderTarget = LoadRenderTexture(WORLD_WIDTH, WORLD_HEIGHT);

    arrpush(shaders, LoadShaderFromMemory(nullptr, nullptr));  // default shader
    arrpush(shaders, LoadShaderFromMemory(nullptr, FRAG_PIXELISER));  // pixelise shader from raylib
    arrpush(shaders, LoadShaderFromMemory(nullptr, FRAG_TORCH));  // light around the mouse

    torchShaderMouseLoc = GetShaderLocation(shaders[2], "mousePos");
    torchShaderResolutionLoc = GetShaderLocation(shaders[2], "resolution");

    // sets shader values that dont have to be set every frame
    Vector2 screenSize = getScreenSize();
    SetShaderValue(shaders[2], torchShaderResolutionLoc, 
        (void*)&screenSize,  SHADER_UNIFORM_VEC2);
}

void FragShaderToy_update([[maybe_unused]] float dt) {
    // not using dt
    if (IsWindowResized()) {
        state.camera.zoom = calculateScreenZoom(WORLD_WIDTH, WORLD_HEIGHT);
        Vector2 screenSize = getScreenSize();
        SetShaderValue(shaders[2], torchShaderResolutionLoc, 
            (void*)&screenSize, SHADER_UNIFORM_VEC2);
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        state.killed = true;
        changeScreen(MENU_SCREEN);
    }

    if (state.killed) return;
    
    if (IsKeyPressed(KEY_H)) {
        state.showGuide = !state.showGuide;
    }

    // waaaaaa shader select is there an easier way? idfk
    if (IsKeyPressed(KEY_ONE)) {
        state.currentShader = 0;
    }
    else if (IsKeyPressed(KEY_TWO)) {
        state.currentShader = 1;
    }
    else if (IsKeyPressed(KEY_THREE)) {
        state.currentShader = 2;
    }

    // set the mouse loc for shaders
    Vector2 mousePos = getMousePositionInvertedY();
    SetShaderValue(shaders[2], torchShaderMouseLoc, 
        (void*)&mousePos, SHADER_UNIFORM_VEC2);
}

void FragShaderToy_draw() {
    if (state.killed) return;
    
    BeginTextureMode(renderTarget);
    DrawTexturePro(prettyPicture, 
        prettyPicture_rect, (Rectangle){0, 0, WORLD_WIDTH, WORLD_HEIGHT}, 
        (Vector2){0,0}, 0.0f, WHITE);
    EndTextureMode();
    
    BeginDrawing();
    ClearBackground(DARKGRAY);
    BeginMode2D(state.camera);

    BeginShaderMode(shaders[state.currentShader]);
    DrawTextureRec(renderTarget.texture, 
        (Rectangle){0, 0, WORLD_WIDTH, -WORLD_HEIGHT}, (Vector2){0,0}, WHITE);
    EndShaderMode();
    
    if (state.showGuide) {
        SimpleText_draw(&guide);
    }
    
    EndMode2D();
    EndDrawing();
}

void FragShaderToy_unload() {
    UnloadTexture(prettyPicture);
    UnloadRenderTexture(renderTarget);

    for (int i = 0; i < arrlen(shaders); i++) {
        UnloadShader(shaders[i]);
    }
    arrfree(shaders);
}
