#pragma once

class AudioManager {
private:
    enum AudioId {
        AUDIO_NONE,

        MUSIC_MENU,
        MUSIC_MAP,
        MUSIC_BABA,

        EFFECT_CONGRATULATION,
        EFFECT_CHANGE_SCENE,
        EFFECT_ENTER_LEVEL,
        EFFECT_RESTART,

        EFFECT_CHOOSE_SETTING,

        EFFECT_CHOOSE_BUTTON_1,
        EFFECT_CHOOSE_BUTTON_2,
        EFFECT_CHOOSE_BUTTON_3,
        EFFECT_CHOOSE_BUTTON_4,
        EFFECT_CHOOSE_BUTTON_5,

        EFFECT_DESCRIPTION_1,
        EFFECT_DESCRIPTION_2,
        EFFECT_DESCRIPTION_3,
        EFFECT_DESCRIPTION_4,
        EFFECT_DESCRIPTION_5,

        EFFECT_MOVE_1,
        EFFECT_MOVE_2,
        EFFECT_MOVE_3,
        EFFECT_MOVE_4,
        EFFECT_MOVE_5,
        EFFECT_MOVE_6,

        EFFECT_UNDO_1,
        EFFECT_UNDO_2,
        EFFECT_UNDO_3,
        EFFECT_UNDO_4,
        EFFECT_UNDO_5,

        EFFECT_DEFEAT_1,
        EFFECT_DEFEAT_2,
        EFFECT_DEFEAT_3,
        EFFECT_DEFEAT_4,

        EFFECT_SINK_1,
        EFFECT_SINK_2,
        EFFECT_SINK_3,
        EFFECT_SINK_4,

        EFFECT_MELT_1,
        EFFECT_MELT_2,
        EFFECT_MELT_3,
        EFFECT_MELT_4,

        EFFECT_OPEN_1,
        EFFECT_OPEN_2,
        EFFECT_OPEN_3,
        EFFECT_OPEN_4,
    };

    static AudioId currentBGM;

public:
    static void Init();

    static void PlayMenuBGM();
    static void PlayMapBGM();
    static void PlayBabaBGM();

    static void PlayCongratulationSound();
    static void PlayChangeSceneSound();
    static void PlayEnterLevelSound();
    static void PlayRestartSound();
    static void PlayChooseSettingSound();
    static void PlayChooseButtonSound();
    static void PlayDescriptionSound();
    static void PlayMoveSound();
    static void PlayUndoSound();
    static void PlayDefeatSound();
    static void PlaySinkSound();
    static void PlayMeltSound();
    static void PlayOpenSound();
};