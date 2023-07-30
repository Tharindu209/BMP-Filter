// includes
#include <gtk/gtk.h>
#include <string.h>
#include "filtering.h"

// macros and Constants
#define LIMIT 100

// global variables
char tmp_in[LIMIT];
char tmp_out[LIMIT];
int option = 1;

// Make all UI parameters in global
GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *windowHead;
GtkWidget *labelInput;
GtkWidget *labelOutput;
GtkWidget *entryin;
GtkWidget *entryout;
GtkWidget *RBGray;
GtkWidget *RBEdge;
GtkWidget *RBReflect;
GtkWidget *RBBlur;
GtkWidget *buttonProcess;
GtkWidget *buttonQuit;
GtkWidget *ImageIn;
GtkWidget *ImageOut;
GtkBuilder *builder;
GdkPixbuf *pixbuf_in;
GdkPixbuf *pixbuf_out;


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("App.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    windowHead = GTK_WIDGET(gtk_builder_get_object(builder, "windowHead"));
    labelInput = GTK_WIDGET(gtk_builder_get_object(builder, "labelInput"));
    labelOutput = GTK_WIDGET(gtk_builder_get_object(builder, "labelOutput"));
    entryin = GTK_WIDGET(gtk_builder_get_object(builder, "entryin"));
    entryout = GTK_WIDGET(gtk_builder_get_object(builder, "entryout"));
    RBGray = GTK_WIDGET(gtk_builder_get_object(builder, "RBGray"));
    RBEdge = GTK_WIDGET(gtk_builder_get_object(builder, "RBEdge"));
    RBReflect = GTK_WIDGET(gtk_builder_get_object(builder, "RBReflect"));
    RBBlur = GTK_WIDGET(gtk_builder_get_object(builder, "RBBlur"));
    buttonProcess = GTK_WIDGET(gtk_builder_get_object(builder, "buttonProcess"));
    buttonQuit = GTK_WIDGET(gtk_builder_get_object(builder, "buttonQuit"));

    // background color
    GdkColor color;
    color.red = 0xcccc;
    color.green = 0xcccc;
    color.blue = 0xd900;
    gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL, &color);

    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}


void update_input_image_preview() {
    // Load input image and update the preview
    pixbuf_in = gdk_pixbuf_new_from_file(tmp_in, NULL);
    GdkPixbuf *scaled_pixbuf_in = gdk_pixbuf_scale_simple(pixbuf_in, 300, 200, GDK_INTERP_BILINEAR);
    if (ImageIn) {
        gtk_widget_destroy(ImageIn);
    }
    ImageIn = gtk_image_new_from_pixbuf(scaled_pixbuf_in);
    gtk_container_add(GTK_CONTAINER(fixed1), ImageIn);
    gtk_widget_show(ImageIn);
    gtk_fixed_move(GTK_FIXED(fixed1), ImageIn, 20, 200);

    g_object_unref(scaled_pixbuf_in);
}

void update_output_image_preview() {
    // Load input image and update the preview
    pixbuf_out = gdk_pixbuf_new_from_file(tmp_out, NULL);
    GdkPixbuf *scaled_pixbuf_out = gdk_pixbuf_scale_simple(pixbuf_out, 300, 200, GDK_INTERP_BILINEAR);
    if (ImageOut) {
        gtk_widget_destroy(ImageOut);
    }
    ImageOut = gtk_image_new_from_pixbuf(scaled_pixbuf_out);
    gtk_container_add(GTK_CONTAINER(fixed1), ImageOut);
    gtk_widget_show(ImageOut);
    gtk_fixed_move(GTK_FIXED(fixed1), ImageOut, 509, 200);

    g_object_unref(scaled_pixbuf_out);
}


void on_entryout_changed(GtkEntry *e) {
    sprintf(tmp_out, "%s", gtk_entry_get_text(e));
}

void on_entryin_changed(GtkEntry *e) {
    sprintf(tmp_in, "%s", gtk_entry_get_text(e));
    update_input_image_preview();
}

void on_RBGray_toggled(GtkRadioButton *b) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b))) {
        option = 1;
    }
}

void on_RBEdge_toggled(GtkRadioButton *b) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b))) {
        option = 2;
    }
}

void on_RBReflect_toggled(GtkRadioButton *b) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b))) {
        option = 3;
    }
}

void on_RBBlur_toggled(GtkRadioButton *b) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b))) {
        option = 4;
    }
}

void on_buttonQuit_clicked(GtkButton *b) {
    gtk_main_quit();
}

void on_buttonProcess_clicked(GtkButton *b) {
    // Apply the selected filter to the input image and save it to the output file
    switch (option) {
        case 1:
            filters('g', tmp_in, tmp_out);
            break;
        case 2:
            filters('e', tmp_in, tmp_out);
            break;
        case 3:
            filters('r', tmp_in, tmp_out);
            break;
        case 4:
            filters('b', tmp_in, tmp_out);
            break;
        default:
            break;
    }
    update_output_image_preview();
}