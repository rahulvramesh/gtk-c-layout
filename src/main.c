#include <gtk/gtk.h>

#define SIDEBAR_ITEM_HEIGHT 40
#define SIDEBAR_FONT_SIZE 14000 // PangoFontDescription uses 1/1000ths of a point

static GtkWidget* create_sidebar_item(const char* label_text) {
    GtkWidget *box, *label;
    GtkStyleContext *context;
    PangoAttrList *attr_list;
    PangoAttribute *attr;

    // Create a box to hold the label and provide padding
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(box, -1, SIDEBAR_ITEM_HEIGHT);

    // Create the label with larger font
    label = gtk_label_new(label_text);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_widget_set_margin_start(label, 10);

    // Set font size
    attr_list = pango_attr_list_new();
    attr = pango_attr_size_new(SIDEBAR_FONT_SIZE);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(label), attr_list);
    pango_attr_list_unref(attr_list);

    gtk_container_add(GTK_CONTAINER(box), label);

    // Add CSS class for styling
    context = gtk_widget_get_style_context(box);
    gtk_style_context_add_class(context, "sidebar-item");

    return box;
}

static void apply_css(void) {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *css =
            ".sidebar-item { border-bottom: 1px solid #cccccc; background-color: #f0f0f0; }"
            ".sidebar-item:hover { background-color: #e0e0e0; }"
            ".sidebar-item:selected { background-color: #d0d0d0; }";
    gtk_css_provider_load_from_data(provider, css, -1, NULL);

    g_object_unref(provider);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *paned;
    GtkWidget *sidebar;
    GtkWidget *main_content;
    GtkWidget *sidebar_list;

    // Apply CSS
    apply_css();

    // Create the main window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Email Client");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Create a paned widget to separate sidebar and main content
    paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), paned);

    // Create the sidebar
    sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(sidebar, 200, -1);  // Set minimum width for sidebar

    // Create a list box for sidebar items
    sidebar_list = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(sidebar), sidebar_list);

    // Add some example items to the sidebar
    const char *sidebar_items[] = {"Inbox", "Sent", "Drafts", "Trash"};
    for (int i = 0; i < G_N_ELEMENTS(sidebar_items); i++) {
        GtkWidget *item = create_sidebar_item(sidebar_items[i]);
        gtk_list_box_insert(GTK_LIST_BOX(sidebar_list), item, -1);
    }

    // Create the main content area (just a placeholder for now)
    main_content = gtk_label_new("Select a folder from the sidebar");

    // Add sidebar and main content to the paned widget
    gtk_paned_pack1(GTK_PANED(paned), sidebar, FALSE, FALSE);
    gtk_paned_pack2(GTK_PANED(paned), main_content, TRUE, FALSE);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.EmailClient", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}