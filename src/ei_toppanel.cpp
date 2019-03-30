#include "ei_toppanel.h"
#include "ei_geometrymanager.h"

namespace ei {


TopPanel::TopPanel() {
    return;
}

TopPanel::TopPanel(Widget *parent):Frame(parent) {}

void TopPanel::configure(const color_t *color,
                    int *border_width,
                    relief_t *relief,
                    const char **text,
                    font_t *text_font,
                    color_t *text_color,
                    anchor_t *text_anchor,
                    surface_t *img,
                    Rect **img_rect,
                    anchor_t *img_anchor,
                    bool closable = true,
                    bool resizable = false,
                    bool reductible = false)
{
    Frame::configure(
        nullptr, color, border_width, relief, text, text_font,
        text_color, text_anchor, img, img_rect, img_anchor
    );

    if (closable) {
        CloseButton = new Frame(this);
        ((Frame *)CloseButton)->configure(
            nullptr,//Just for the moment
            new color_t({230, 30, 30, 255}),
            nullptr,
            nullptr,
            new char*("X"),
            nullptr,
            new color_t({40, 40, 40, 255}),
            new anchor_t(ei_anc_center),
            Frame::getImg(),
            nullptr, //Hum maybe will cause problems....
            nullptr
        );

        Placer *CloseButtonPlacer = new Placer();
        CloseButtonPlacer->configure(
            CloseButton,
            nullptr,
            new int(10), new int(10),
            new float(15), new float(15),
            nullptr, nullptr, nullptr, nullptr
        );
    } else {
        CloseButton = nullptr;
    }

    //Not implemented for the moment
    ReduceButton = nullptr;
    ResizeButton = nullptr;

}

void TopPanel::geomnotify(Rect rect){
    Frame::geomnotify(rect);

    if (CloseButton) {
        CloseButton->getGeometryManager()->run(CloseButton);
    }

    if (ReduceButton) {
        ReduceButton->getGeometryManager()->run(ReduceButton);
    }

    if (ResizeButton) {
        ResizeButton->getGeometryManager()->run(ResizeButton);
    }
}

void TopPanel::draw(surface_t surface, surface_t pick_surface, Rect *clipper) {
    Frame::draw(surface, pick_surface, clipper);

    //Drawing all children
    std::list<Widget *> l;
    for (std::list<Widget *>::iterator it = (l = getChildren()).begin(); it != l.end(); ++it)
    {
        (*it)->draw(surface, pick_surface, clipper);
        continue;
    }

    if (CloseButton)
    {
        CloseButton->draw(surface, pick_surface, clipper);
    }

    if (ReduceButton)
    {
        ReduceButton->draw(surface, pick_surface, clipper);
    }

    if (ResizeButton)
    {
        ResizeButton->draw(surface, pick_surface, clipper);
    }
}

}