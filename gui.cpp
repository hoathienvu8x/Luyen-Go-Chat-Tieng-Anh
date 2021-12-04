#include <gtk/gtk.h>

struct chat_t {
    GtkWidget *entry;
    GtkWidget *textview;
};

void chatMSG ( GtkButton *, chat_t * );

int main ( int argc, char **argv ) {
    GtkWidget *window, *scrolled_win, *hbox, *vbox, *button;
    chat_t *chat = g_slice_new ( chat_t );

    gtk_init(&argc, &argv);

    window = gtk_window_new ( GTK_WINDOW_TOPLEVEL );
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect ( G_OBJECT ( window ), "delete_event", gtk_main_quit, NULL );
    gtk_window_set_title ( GTK_WINDOW ( window ), "WhatsChat" );
    gtk_container_set_border_width ( GTK_CONTAINER ( window ), 0 );
    gtk_widget_set_size_request ( window, 350, 250 );
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    // *** //
    chat->textview = gtk_text_view_new();
    gtk_text_view_set_editable ( GTK_TEXT_VIEW ( chat->textview ), FALSE );
    gtk_text_view_set_cursor_visible ( GTK_TEXT_VIEW ( chat->textview ), FALSE );
    // *** //
    GtkTextBuffer *buffer = gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( chat->textview ) );
    gtk_text_buffer_create_tag(buffer, "gap",
        "pixels_above_lines", 5,
        "wrap_mode", GTK_WRAP_WORD,
        "direction", GTK_TEXT_DIR_LTR,
        "left_margin", 10,
        "right_margin", 10
    , NULL);
    gtk_text_buffer_create_tag(buffer, "blue_fg", "foreground", "blue", NULL);
    gtk_text_buffer_create_tag(buffer, "red_fg", "foreground", "red", NULL);
    gtk_text_buffer_create_tag(buffer, "gray_fg", "foreground", "gray", NULL);
    gtk_text_buffer_create_tag(buffer, "bold","weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_buffer_create_tag(buffer, "italic", "style", PANGO_STYLE_ITALIC, NULL);
    // *** //
    chat->entry = gtk_entry_new();
    gtk_widget_set_hexpand(chat->entry, TRUE);
    button = gtk_button_new_with_label ( "Send" );
    // *** //
    g_signal_connect ( G_OBJECT ( button      ), "clicked",  G_CALLBACK ( chatMSG ), ( gpointer ) chat );
    g_signal_connect ( G_OBJECT ( chat->entry ), "activate", G_CALLBACK ( chatMSG ), ( gpointer ) chat );
    // *** //
    scrolled_win = gtk_scrolled_window_new ( NULL, NULL );
    gtk_widget_set_size_request ( scrolled_win, -1, 200 );
    gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scrolled_win ), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );
    gtk_container_add ( GTK_CONTAINER ( scrolled_win ), chat->textview );
    // *** //
    hbox = gtk_box_new ( GTK_ORIENTATION_HORIZONTAL, 0 );
    gtk_box_pack_start ( GTK_BOX ( hbox ), chat->entry, FALSE, TRUE, 0 );
    gtk_box_pack_start ( GTK_BOX ( hbox ), button, FALSE, TRUE, 1 );
    // *** //
    vbox = gtk_box_new ( GTK_ORIENTATION_VERTICAL, 0 );
    gtk_box_pack_start ( GTK_BOX ( vbox ), scrolled_win, TRUE, TRUE, 0 );
    gtk_box_pack_start ( GTK_BOX ( vbox ), hbox, FALSE, TRUE, 0 );
    gtk_container_add ( GTK_CONTAINER ( window ), vbox );
    // *** //

    gtk_widget_show_all ( window );
    gtk_main();

    return 0;
}

void chatMSG ( GtkButton *button, chat_t *chat ) {
    ( void )button;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( chat->textview ) );
    const gchar *text     = gtk_entry_get_text ( GTK_ENTRY ( chat->entry ) );
    GtkTextMark *mark = gtk_text_buffer_get_insert ( buffer );
    GtkTextIter iter;

    gtk_text_buffer_get_iter_at_mark ( buffer, &iter, mark );
    if (  gtk_text_buffer_get_char_count ( buffer ) && g_utf8_strlen( text, -1 ) > 0) {
        gtk_text_buffer_insert ( buffer, &iter, "\n", -1 );
    }
    
    gtk_text_buffer_insert_with_tags_by_name(buffer, &iter,"You: ", -1, "gap","blue_fg", "bold",  NULL);
    gtk_text_buffer_insert ( buffer, &iter, text, -1 );
    gtk_text_buffer_insert_with_tags_by_name(buffer, &iter,"\nBot: ", -1, "gap", "red_fg", "bold",  NULL);
    gtk_text_buffer_insert_with_tags_by_name ( buffer, &iter, "oh hi there", -1, "italic", "gray_fg", NULL );

    gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW ( chat->textview ), mark);

    gtk_entry_set_text ( GTK_ENTRY ( chat->entry ), "" );
}