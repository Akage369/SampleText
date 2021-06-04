#ifndef SCENE_INTRO_H
#define SCENE_INTRO_H

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
class SceneIntro : public Module {
public:
    SceneIntro(bool startEnabled);

    ~SceneIntro();

    bool Start() override;

    //updates the scene's background animations
    update_status Update() override;

    //forms the render call of all the parts of the scene's backgroud
    update_status PostUpdate() override;

public:

    //sprite loaded into an SDL_Texture
    SDL_Texture* bgTexture = nullptr;
    SDL_Texture* bgTexture1 = nullptr;
    //The intro animation 
    Animation intro;
    Animation logo;
};

#endif