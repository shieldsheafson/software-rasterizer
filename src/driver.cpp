#include "model.h"
#include "rasterizerconfig.h"
#include "rendertarget.h"
#include "transform.h"
#include "utils.h"

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

static int screenWidth = 1000;
static int screenHeight = 700;
static RenderTarget renderTarget(screenWidth, screenHeight);

static Model<float> model("../input/cube.obj");
static Transform<float> transform(0.0, 0.01, 0.0);

static int times = 0;

// Init
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_SetAppMetadata("Software Rasterizer", 
                     RASTERIZER_VERSION_STRING, 
                     "com.rasterizer");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("Software Rasterizer", screenWidth, screenHeight, SDL_WINDOW_INPUT_FOCUS, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, screenWidth, screenHeight);
  if (!texture) {
    SDL_Log("Couldn't create streaming texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

// Event Handler
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  // Exit gracefully
    }
    return SDL_APP_CONTINUE;
}

// Runs once each frame
SDL_AppResult SDL_AppIterate(void *appstate) {
  times++;
  void *pixels;
  int pitch; // the pitch is the length of one row in bytes
  SDL_LockTexture(texture, NULL, &pixels, &pitch);
  renderTarget.SetPixels(pixels);
  renderTarget.SetPitch(pitch);
  renderTarget.Clear();

  if (times == 50) {
    transform.SetPitch(0.01);
    transform.SetYaw(0.0);
  }

  model.Transform(transform);
  Render(model, renderTarget);

  SDL_UnlockTexture(texture);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderTexture(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  /* SDL will clean up the window/renderer for us. */
  SDL_DestroyTexture(texture);
  texture = NULL;
}
