#include "camera.h"
#include "model.h"
#include "rasterizerconfig.h"
#include "rendertarget.h"
#include "transform.h"
#include "utils.h"

#include <cmath>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

static int screenWidth = 1000;
static int screenHeight = 700;
static RenderTarget renderTarget(screenWidth, screenHeight);

static Model model("../input/cube.obj");
Model model2("../input/monkey.obj");
static Transform transform(0.0, 0.0, 0.0, Point3(0,0,0));
static Camera camera = Camera();

static int start;
static int times = 0;

static float movementSpeed = 1;
static float panSpeed = 0.5;
static Uint64 lastFrameTime = 0;

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

  start = SDL_GetTicks();

  return SDL_APP_CONTINUE;
}

// Event Handler
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  // Exit gracefully
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      transform.SetPitch(0);
      transform.SetYaw(0);
      transform.SetRoll(0);
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
      transform.SetPitch(0.01);
      transform.SetYaw(0.01);
      transform.SetRoll(0);
    }

    return SDL_APP_CONTINUE;
}

// Runs once each frame
SDL_AppResult SDL_AppIterate(void *appstate) {
  Uint64 currentTime = SDL_GetTicks();
  float deltaTime = (currentTime - lastFrameTime) / 1000.0f; // Convert to seconds
  lastFrameTime = currentTime;
  
  const bool *keystate = SDL_GetKeyboardState(NULL);
  
  if (keystate[SDL_SCANCODE_UP]) {
      camera.Forward(movementSpeed * deltaTime);
  }
  if (keystate[SDL_SCANCODE_DOWN]) {
      camera.Backward(movementSpeed * deltaTime);
  }
  if (keystate[SDL_SCANCODE_LEFT]) {
      camera.Left(movementSpeed * deltaTime);
  }
  if (keystate[SDL_SCANCODE_RIGHT]) {
      camera.Right(movementSpeed * deltaTime);
  }
  if (keystate[SDL_SCANCODE_Z]) {
      camera.PanLeft(panSpeed * deltaTime);
  }
  if (keystate[SDL_SCANCODE_X]) {
      camera.PanRight(panSpeed * deltaTime);
  }

  times++;
  void *pixels;
  int pitch; // the pitch is the length of one row in bytes
  SDL_LockTexture(texture, NULL, &pixels, &pitch);
  renderTarget.SetPixels(pixels);
  renderTarget.SetPitch(pitch);
  renderTarget.Clear();

  model.TransformModel(transform);
  Render(model, Point3(-2, 0, 5), renderTarget, camera);
  Render(model2, Point3(2, 0, -5), renderTarget, camera);

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
  int now = SDL_GetTicks();
  int elapsed = static_cast<double>(now - start) / 1000.0;
  double fps = static_cast<double>(times) / elapsed;
  std::cout << "FPS: " << fps << std::endl;
  SDL_DestroyTexture(texture);
  texture = NULL;
}
