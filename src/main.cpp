#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

// ── Click counter label — shown in top-left during gameplay ──────────────
// We store the label as a static pointer reset each level.
static CCLabelBMFont* s_label = nullptr;
static int            s_clicks = 0;

static void updateLabel() {
    if (!s_label) return;
    auto text = fmt::format("CC: {}", s_clicks);
    s_label->setString(text.c_str());
}

// ── Hook PlayLayer — create/destroy the label with the level ─────────────
class $modify(CCClickPlayLayer, PlayLayer) {

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        s_clicks = 0;
        s_label  = nullptr;

        auto winSize = CCDirector::get()->getWinSize();

        // Create label using the GD bitmap font
        s_label = CCLabelBMFont::create("CC: 0", "bigFont.fnt");
        s_label->setScale(0.45f);
        s_label->setOpacity(200);
        s_label->setAnchorPoint({ 0.f, 1.f }); // top-left anchor
        s_label->setPosition({ 6.f, winSize.height - 6.f });
        s_label->setZOrder(100); // on top of everything

        this->addChild(s_label);

        return true;
    }

    // Called when the level is exited / completed — clean up
    void onQuit() {
        s_label  = nullptr;
        s_clicks = 0;
        PlayLayer::onQuit();
    }

    // Reset clicks on restart too
    void resetLevel() {
        s_clicks = 0;
        updateLabel();
        PlayLayer::resetLevel();
    }
};

// ── Hook GJBaseGameLayer — intercept player input to count clicks ─────────
// pushButton is called on EVERY input (jump, left, right) for both players.
// playerButton 0 = jump/main, 1 = secondary — we count all of them.
class $modify(CCClickBaseLayer, GJBaseGameLayer) {
    void handleButton(bool down, int button, bool isPlayer1) {
        // Only count presses (down=true), not releases
        if (down) {
            s_clicks++;
            updateLabel();
        }
        GJBaseGameLayer::handleButton(down, button, isPlayer1);
    }
};