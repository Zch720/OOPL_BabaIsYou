#include "stdafx.h"
#include <stdlib.h>
#include "audio_manager.h"
#include "../../Library/audio.h"

using namespace game_framework;

AudioManager::AudioId AudioManager::currentBGM = MUSIC_BABA;
bool AudioManager::isMusicOn = true;
bool AudioManager::isSoundOn = true;

void AudioManager::Init() {
	//CAudio::Instance()->Open();

    CAudio::Instance()->Load(MUSIC_MENU, "./resources/audio/music/menu.wav");
    CAudio::Instance()->Load(MUSIC_MAP, "./resources/audio/music/map.wav");
    CAudio::Instance()->Load(MUSIC_BABA, "./resources/audio/music/baba.wav");

    CAudio::Instance()->Load(EFFECT_CONGRATULATION, "./resources/audio/sound/congratulation.wav");
    CAudio::Instance()->Load(EFFECT_CHANGE_SCENE, "./resources/audio/sound/change_scene.wav");
    CAudio::Instance()->Load(EFFECT_ENTER_LEVEL, "./resources/audio/sound/enter_level.wav");
    CAudio::Instance()->Load(EFFECT_RESTART, "./resources/audio/sound/restart.wav");
    CAudio::Instance()->Load(EFFECT_CHOOSE_SETTING, "./resources/audio/sound/choose_setting.wav");
    CAudio::Instance()->Load(EFFECT_CHOOSE_BUTTON_1, "./resources/audio/sound/button_1.wav");
    CAudio::Instance()->Load(EFFECT_CHOOSE_BUTTON_2, "./resources/audio/sound/button_2.wav");
    CAudio::Instance()->Load(EFFECT_CHOOSE_BUTTON_3, "./resources/audio/sound/button_3.wav");
    CAudio::Instance()->Load(EFFECT_CHOOSE_BUTTON_4, "./resources/audio/sound/button_4.wav");
    CAudio::Instance()->Load(EFFECT_CHOOSE_BUTTON_5, "./resources/audio/sound/button_5.wav");
    CAudio::Instance()->Load(EFFECT_DESCRIPTION_1, "./resources/audio/sound/description_1.wav");
    CAudio::Instance()->Load(EFFECT_DESCRIPTION_2, "./resources/audio/sound/description_2.wav");
    CAudio::Instance()->Load(EFFECT_DESCRIPTION_3, "./resources/audio/sound/description_3.wav");
    CAudio::Instance()->Load(EFFECT_DESCRIPTION_4, "./resources/audio/sound/description_4.wav");
    CAudio::Instance()->Load(EFFECT_DESCRIPTION_5, "./resources/audio/sound/description_5.wav");
    CAudio::Instance()->Load(EFFECT_MOVE_1, "./resources/audio/sound/move_1.wav");
    CAudio::Instance()->Load(EFFECT_MOVE_2, "./resources/audio/sound/move_2.wav");
    CAudio::Instance()->Load(EFFECT_MOVE_3, "./resources/audio/sound/move_3.wav");
    CAudio::Instance()->Load(EFFECT_MOVE_4, "./resources/audio/sound/move_4.wav");
    CAudio::Instance()->Load(EFFECT_MOVE_5, "./resources/audio/sound/move_5.wav");
    CAudio::Instance()->Load(EFFECT_MOVE_6, "./resources/audio/sound/move_6.wav");
    CAudio::Instance()->Load(EFFECT_UNDO_1, "./resources/audio/sound/undo_1.wav");
    CAudio::Instance()->Load(EFFECT_UNDO_2, "./resources/audio/sound/undo_2.wav");
    CAudio::Instance()->Load(EFFECT_UNDO_3, "./resources/audio/sound/undo_3.wav");
    CAudio::Instance()->Load(EFFECT_UNDO_4, "./resources/audio/sound/undo_4.wav");
    CAudio::Instance()->Load(EFFECT_UNDO_5, "./resources/audio/sound/undo_5.wav");
    CAudio::Instance()->Load(EFFECT_DEFEAT_1, "./resources/audio/sound/defeat_1.wav");
    CAudio::Instance()->Load(EFFECT_DEFEAT_2, "./resources/audio/sound/defeat_2.wav");
    CAudio::Instance()->Load(EFFECT_DEFEAT_3, "./resources/audio/sound/defeat_3.wav");
    CAudio::Instance()->Load(EFFECT_DEFEAT_4, "./resources/audio/sound/defeat_4.wav");
    CAudio::Instance()->Load(EFFECT_SINK_1, "./resources/audio/sound/sink_1.wav");
    CAudio::Instance()->Load(EFFECT_SINK_2, "./resources/audio/sound/sink_2.wav");
    CAudio::Instance()->Load(EFFECT_SINK_3, "./resources/audio/sound/sink_3.wav");
    CAudio::Instance()->Load(EFFECT_SINK_4, "./resources/audio/sound/sink_4.wav");
    CAudio::Instance()->Load(EFFECT_MELT_1, "./resources/audio/sound/melt_1.wav");
    CAudio::Instance()->Load(EFFECT_MELT_2, "./resources/audio/sound/melt_2.wav");
    CAudio::Instance()->Load(EFFECT_MELT_3, "./resources/audio/sound/melt_3.wav");
    CAudio::Instance()->Load(EFFECT_MELT_4, "./resources/audio/sound/melt_4.wav");
    CAudio::Instance()->Load(EFFECT_OPEN_1, "./resources/audio/sound/open_1.wav");
    CAudio::Instance()->Load(EFFECT_OPEN_2, "./resources/audio/sound/open_2.wav");
    CAudio::Instance()->Load(EFFECT_OPEN_3, "./resources/audio/sound/open_3.wav");
    CAudio::Instance()->Load(EFFECT_OPEN_4, "./resources/audio/sound/open_4.wav");
}

void AudioManager::SetMusicOn(bool isOn) {
    if (isMusicOn == isOn) return;
    isMusicOn = isOn;
    if (!isOn) {
        CAudio::Instance()->Stop(currentBGM);
    } else {
        CAudio::Instance()->Play(currentBGM, true);
    }
}

void AudioManager::SetSoundOn(bool isOn) {
    if (isSoundOn == isOn) return;
    isSoundOn = isOn;
}

void AudioManager::PlayMenuBGM() {
    if (currentBGM != MUSIC_MENU) {
        currentBGM = MUSIC_MENU;
        if (!isMusicOn) return;
        CAudio::Instance()->Stop(MUSIC_MAP);
        CAudio::Instance()->Stop(MUSIC_BABA);
        CAudio::Instance()->Play(MUSIC_MENU, true);
    }
}

void AudioManager::PlayMapBGM() {
    if (currentBGM != MUSIC_MAP) {
        currentBGM = MUSIC_MAP;
        if (!isMusicOn) return;
        CAudio::Instance()->Stop(MUSIC_MENU);
        CAudio::Instance()->Stop(MUSIC_BABA);
        CAudio::Instance()->Play(MUSIC_MAP, true);
    }
}

void AudioManager::PlayBabaBGM() {
    if (currentBGM != MUSIC_BABA) {
        currentBGM = MUSIC_BABA;
        if (!isMusicOn) return;
        CAudio::Instance()->Stop(MUSIC_MENU);
        CAudio::Instance()->Stop(MUSIC_MAP);
        CAudio::Instance()->Play(MUSIC_BABA, true);
    }
}

void AudioManager::PlayCongratulationSound() {
    if (!isSoundOn) return;
    CAudio::Instance()->Play(EFFECT_CONGRATULATION);
}

void AudioManager::PlayChangeSceneSound() {
    if (!isSoundOn) return;
    CAudio::Instance()->Play(EFFECT_CHANGE_SCENE);
}

void AudioManager::PlayEnterLevelSound() {
    if (!isSoundOn) return;
    CAudio::Instance()->Play(EFFECT_ENTER_LEVEL);
}

void AudioManager::PlayRestartSound() {
    if (!isSoundOn) return;
    CAudio::Instance()->Play(EFFECT_RESTART);
}

void AudioManager::PlayChooseSettingSound() {
    if (!isSoundOn) return;
    CAudio::Instance()->Play(EFFECT_CHOOSE_SETTING);
}

void AudioManager::PlayChooseButtonSound() {
    if (!isSoundOn) return;
    int rand = std::rand() % 5;
    if (rand == 0) {
        CAudio::Instance()->Play(EFFECT_CHOOSE_BUTTON_1);
    }
    else if (rand == 1) {
        CAudio::Instance()->Play(EFFECT_CHOOSE_BUTTON_2);
    }
    else if (rand == 2) {
        CAudio::Instance()->Play(EFFECT_CHOOSE_BUTTON_3);
    }
    else if (rand == 3) {
        CAudio::Instance()->Play(EFFECT_CHOOSE_BUTTON_4);
    }
    else if (rand == 4) {
        CAudio::Instance()->Play(EFFECT_CHOOSE_BUTTON_5);
    }
}

void AudioManager::PlayDescriptionSound() {
    if (!isSoundOn) return;
    int rand = std::rand() % 5;
    if (rand == 0) {
        CAudio::Instance()->Play(EFFECT_DESCRIPTION_1);
    }
    else if (rand == 1) {
        CAudio::Instance()->Play(EFFECT_DESCRIPTION_2);
    }
    else if (rand == 2) {
        CAudio::Instance()->Play(EFFECT_DESCRIPTION_3);
    }
    else if (rand == 3) {
        CAudio::Instance()->Play(EFFECT_DESCRIPTION_4);
    }
    else if (rand == 4) {
        CAudio::Instance()->Play(EFFECT_DESCRIPTION_5);
    }
}

void AudioManager::PlayMoveSound() {
    if (!isSoundOn) return;
    int rand = std::rand() % 6;
    if (rand == 0) {
        CAudio::Instance()->Play(EFFECT_MOVE_1);
    }
    else if (rand == 1) {
        CAudio::Instance()->Play(EFFECT_MOVE_2);
    }
    else if (rand == 2) {
        CAudio::Instance()->Play(EFFECT_MOVE_3);
    }
    else if (rand == 3) {
        CAudio::Instance()->Play(EFFECT_MOVE_4);
    }
    else if (rand == 4) {
        CAudio::Instance()->Play(EFFECT_MOVE_5);
    }
    else if (rand == 5) {
        CAudio::Instance()->Play(EFFECT_MOVE_6);
    }
}

void AudioManager::PlayUndoSound() {
    if (!isSoundOn) return;
    int rand = std::rand() % 5;
    if (rand == 0) {
        CAudio::Instance()->Play(EFFECT_UNDO_1);
    }
    else if (rand == 1) {
        CAudio::Instance()->Play(EFFECT_UNDO_2);
    }
    else if (rand == 2) {
        CAudio::Instance()->Play(EFFECT_UNDO_3);
    }
    else if (rand == 3) {
        CAudio::Instance()->Play(EFFECT_UNDO_4);
    }
    else if (rand == 4) {
        CAudio::Instance()->Play(EFFECT_UNDO_5);
    }
}

void AudioManager::PlayDefeatSound() {
    if (!isSoundOn) return;
    int rand = std::rand() % 4;
    if (rand == 0) {
        CAudio::Instance()->Play(EFFECT_DEFEAT_1);
    }
    else if (rand == 1) {
        CAudio::Instance()->Play(EFFECT_DEFEAT_2);
    }
    else if (rand == 2) {
        CAudio::Instance()->Play(EFFECT_DEFEAT_3);
    }
    else if (rand == 3) {
        CAudio::Instance()->Play(EFFECT_DEFEAT_4);
    }
}

void AudioManager::PlaySinkSound() {
    if (!isSoundOn) return;
    int rand = std::rand() % 4;
    if (rand == 0) {
        CAudio::Instance()->Play(EFFECT_SINK_1);
    }
    else if (rand == 1) {
        CAudio::Instance()->Play(EFFECT_SINK_2);
    }
    else if (rand == 2) {
        CAudio::Instance()->Play(EFFECT_SINK_3);
    }
    else if (rand == 3) {
        CAudio::Instance()->Play(EFFECT_SINK_4);
    }
}

void AudioManager::PlayMeltSound() {
    if (!isSoundOn) return;
    int rand = std::rand() % 4;
    if (rand == 0) {
        CAudio::Instance()->Play(EFFECT_MELT_1);
    }
    else if (rand == 1) {
        CAudio::Instance()->Play(EFFECT_MELT_2);
    }
    else if (rand == 2) {
        CAudio::Instance()->Play(EFFECT_MELT_3);
    }
    else if (rand == 3) {
        CAudio::Instance()->Play(EFFECT_MELT_4);
    }
}

void AudioManager::PlayOpenSound() {
    if (!isSoundOn) return;
    int rand = std::rand() % 4;
    if (rand == 0) {
        CAudio::Instance()->Play(EFFECT_OPEN_1);
    }
    else if (rand == 1) {
        CAudio::Instance()->Play(EFFECT_OPEN_2);
    }
    else if (rand == 2) {
        CAudio::Instance()->Play(EFFECT_OPEN_3);
    }
    else if (rand == 3) {
        CAudio::Instance()->Play(EFFECT_OPEN_4);
    }
}