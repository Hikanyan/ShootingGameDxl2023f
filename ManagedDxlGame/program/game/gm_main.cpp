#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "../hikanyan_library/scene/SceneManager.h"
#include "../hikanyan_library/scene/SampleScene.h"
#include "hikanyan_laboratory/scene/TitleScene.h"
//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart()
{
    srand(time(0));
    SetBackgroundColor(32, 32, 32);

    auto sampleScene = std::make_shared<TitleScene>();
    
    SceneManager::getInstance()->add_scene("TitleScene", sampleScene);
    SceneManager::getInstance()->load_scene("TitleScene");
    SceneManager::getInstance()->game_start();
}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time)
{
    DrawFpsIndicator({10, DXE_WINDOW_HEIGHT - 10, 0}, delta_time);
    SceneManager::getInstance()->game_main(delta_time);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd()
{
    SceneManager::getInstance()->game_end();
}
