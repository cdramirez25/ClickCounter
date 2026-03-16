#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

static int s_clicks = 0;
static CCLabelBMFont* s_label = nullptr;

static void updateLabel() {
    if (!s_label) return;
    s_label->setString(fmt::format("CC: {}", s_clicks).c_str());
}

class $modify(MyPlayLayer, PlayLayer) {

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        s_clicks = 0;
        s_label = nullptr;

        auto winSize = CCDirector::get()->getWinSize();

        s_label = CCLabelBMFont::create("CC: 0", "bigFont.fnt");
        s_label->setScale(0.45f);
        s_label->setOpacity(150); // semi-transparente
        s_label->setAnchorPoint({ 0.f, 1.f });
        s_label->setPosition({ 6.f, winSize.height - 6.f });
        s_label->setZOrder(100);
        this->addChild(s_label);

        return true;
    }

    void onQuit() {
        s_label = nullptr;
        s_clicks = 0;
        PlayLayer::onQuit();
    }

    void resetLevel() {
        s_clicks = 0;
        updateLabel();
        PlayLayer::resetLevel();
    }
};

class $modify(MyBaseLayer, GJBaseGameLayer) {

    void handleButton(bool down, int button, bool isPlayer1) {
        GJBaseGameLayer::handleButton(down, button, isPlayer1);
        if (down && PlayLayer::get()) {
            s_clicks++;
            updateLabel();
        }
    }
};