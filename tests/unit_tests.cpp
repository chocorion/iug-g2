#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "ei_main.h"
#include "ei_application.h"
#include "ei_draw.h"
#include "hw_interface.h"
#include "ei_geometrymanager.h"
#include "ei_widget.h"
#include "ei_eventmanager.h"
#include <iostream>

using namespace std;

using namespace ei;

TEST_CASE("create_window", "[unit]")
{
    surface_t main_window = NULL;
    Size main_window_size(640,480), query_size;

    main_window = hw_create_window(&main_window_size, EI_FALSE);
    REQUIRE( main_window != NULL );

    query_size = hw_surface_get_size(main_window);
    REQUIRE( main_window_size.width()  == query_size.width() );
    REQUIRE( main_window_size.height() == query_size.height() );

}

TEST_CASE("fill_window", "[unit]")
{
    surface_t main_window = NULL;
    Size main_window_size(640,480), query_size;
    color_t red = {0xff, 0x00, 0x00, 0xff}, query_color;
    Point origin;

    main_window = hw_create_window(&main_window_size, EI_FALSE);

    SECTION( "fill_red" ) {
        fill(main_window, &red, EI_FALSE);
        hw_surface_update_rects(linked_rect_t());

        query_color = hw_get_pixel(main_window, origin);
        REQUIRE( query_color.red == red.red );
        REQUIRE( query_color.green == red.green );
        REQUIRE( query_color.blue == red.blue );
    }

    SECTION( "fill_default" ) {
        fill(main_window, NULL, EI_FALSE);
        hw_surface_update_rects(linked_rect_t());

        query_color = hw_get_pixel(main_window, origin);
        REQUIRE( query_color.red == font_default_color.red );
        REQUIRE( query_color.green == font_default_color.green );
        REQUIRE( query_color.blue == font_default_color.blue );
    }

}

TEST_CASE("placer", "[unit]")
{
    cout << "Test Placer" << endl;
    SECTION("configure") 
    {
        cout << "\tSection configure" << endl;
        Widget w = Widget("test", nullptr);
        Placer p = Placer();

        p.configure(
            &w, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr
        );
        REQUIRE( w.getGeometryManager() == &p);
    }
    
    SECTION("remove")
    {
        cout << "\tSection configure" << endl;
        Widget w = Widget("test", nullptr);
        Placer p = Placer();

        p.configure(
            &w, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr, 
            nullptr
        );
        p.release(&w);

        //Just look if it crash due to pointers
        REQUIRE(true);
    }

}

TEST_CASE("Simple_geometryManager" , "[unit]")
{  
    cout << "---------------------------------------" << endl;
    cout << "Test geometryManager " << endl;
    Value<int> v(42, true);
    cout << v.getValue() << " " << v.isDefault() << endl;
    //Juste histoire que make me lance la compilation du géométrie manager

    Widget w = Widget("test", nullptr);
    Placer c = Placer();

    c.configure(
        &w, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);


        REQUIRE(true);
}

TEST_CASE("Create widget" , "[unit]")
{  
    cout << "---------------------------------------" << endl;
    cout << "Test widget (frame) " << endl;
    
    Size frame_size = Size(300, 200);
    color_t frame_color = { 0x88, 0x88, 0x88, 0xff };
    relief_t frame_relief = ei_relief_raised;
    int frame_border_width = 6;

    Frame* frame = new Frame(new Widget("root",nullptr));
    
    frame->configure(&frame_size, &frame_color, &frame_border_width,
                     &frame_relief, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    cout << "Widget id : " << frame->getPick_id() << endl;
    cout << "Widget pick color : (" << (int) frame->get_pick_color().red 
    << "," << (int) frame->get_pick_color().green 
    << "," << (int) frame->get_pick_color().blue 
    << "," << (int) frame->get_pick_color().alpha << ")" << endl;

    SECTION("Parent/Child")
    {
        Widget* w = new Widget("root",nullptr);
        Frame* frame = new Frame(w);
        std::list<Widget*> l = w->getChildren();

        REQUIRE(l.size() == 1);
    }

    REQUIRE(true);
}

TEST_CASE("Create frame" , "[unit]")
{  
    cout << "---------------------------------------" << endl;
    cout << "Test frame " << endl;
    
    Size frame_size = Size(300, 200);
    color_t frame_color = { 0x88, 0x88, 0x88, 0xff };
    relief_t frame_relief = ei_relief_raised;
    int frame_border_width = 6;

    Frame* frame = new Frame(new Widget("root",nullptr));
    
    frame->configure(&frame_size, &frame_color, &frame_border_width,
                     &frame_relief, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    REQUIRE(true);
}

TEST_CASE("create Application", "[unit]")
{
    Size screen_size = Size(600, 600);
    Application* app = new Application(&screen_size);

    REQUIRE(app != nullptr);
}

TEST_CASE("configure Application", "[unit]")
{
    color_t root_bgcol = { 0x52, 0x7f, 0xb4, 0xff };
    Size screen_size = Size(600, 600);
    Application* app = new Application(&screen_size);

    app->root_widget()->configure(&screen_size, &root_bgcol, NULL, NULL, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL);

    REQUIRE(app != nullptr);
}

TEST_CASE("configure Application Frame", "[unit]")
{    
    Size screen_size = Size(600, 600);
    color_t root_bgcol = { 0x52, 0x7f, 0xb4, 0xff };

    Size frame_size = Size(300, 200);
    color_t frame_color = { 0x88, 0x88, 0x88, 0xff };
    relief_t frame_relief = ei_relief_raised;
    int frame_border_width = 6;

    Application* app = new Application(&screen_size);
    app->root_widget()->configure(&screen_size, &root_bgcol, NULL, NULL, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL);

    Frame* frame = new Frame(app->root_widget());
    frame->configure(&frame_size, &frame_color, &frame_border_width,
                     &frame_relief, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    REQUIRE(app != nullptr);
}

TEST_CASE("BoundEventBank", "[unit]")
{
    BoundEventBank bank;
    BoundEvent *data = new BoundEvent(
        nullptr, 
        "all",
        nullptr, 
        nullptr
    );

    bank.add(ei_ev_none, data);

    SECTION("get")
    {
        std::list<BoundEvent*> *data;
        REQUIRE(((data = bank.get(ei_ev_none)) && data->size() == 1));
    }

    SECTION("remove")
    {
        bank.remove(ei_ev_none, data);
        REQUIRE(bank.get(ei_ev_none)->size() == 0);
    }
    REQUIRE(true);
}

int ei_main(int argc, char* argv[])
{
    // Init acces to hardware.
    hw_init();

    int result = Catch::Session().run( argc, argv );

    // Free hardware resources.
    hw_quit();

    return result;
}
