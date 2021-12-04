#include <gtk/gtk.h>
#include <algorithm>
#include <string>
#include <json.h>
#include <util.h>

struct chat_t {
    GtkWidget *entry;
    GtkWidget *textview;
};
enum {
    LIST_ITEM = 0,
    LIST_INDEX,
    N_COLUMNS
};
struct item_t {
    std::string en;
    std::string vi;
};
struct topic_t {
    item_t topic;
    std::vector<item_t> items;
};
std::vector<topic_t> topics;
topic_t topic;
size_t current_index = 0;
size_t hint = 5;
size_t trying = 0;

void chatMSG ( GtkButton *, chat_t * );
void change_topic(GtkWidget *, gpointer);
void initBotMessage( GtkWidget *, gchar * );
std::vector<topic_t> load_topics( std::string );
std::string toLowerCase(std::string);

int main ( int argc, char **argv ) {
    GtkWidget *window, *scrolled_win, *hbox, *vbox, *button;
    chat_t *chat = g_slice_new ( chat_t );

    gtk_init(&argc, &argv);

    window = gtk_window_new ( GTK_WINDOW_TOPLEVEL );
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect ( G_OBJECT ( window ), "delete_event", gtk_main_quit, NULL );
    gtk_window_set_title ( GTK_WINDOW ( window ), "WhatsChat" );
    gtk_container_set_border_width ( GTK_CONTAINER ( window ), 0 );
    gtk_widget_set_size_request ( window, 550, 250 );
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    if ( ! g_file_test ("topics.json", G_FILE_TEST_EXISTS) ) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, (gchar *)"topics.json is not found.");
        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy (dialog);
        return 0;
    }
    if (g_file_test ("favicon.png",G_FILE_TEST_EXISTS)) {
        GdkPixbuf *icon = gdk_pixbuf_new_from_file("favicon.png", NULL);
        if (icon) {
            gtk_window_set_icon(GTK_WINDOW(window), icon);
        }
    }
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
    // *** //
    GtkWidget *gbox = gtk_box_new ( GTK_ORIENTATION_VERTICAL, 0 );
    GtkWidget *list = gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new ();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Topics", renderer, "text", LIST_ITEM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    GtkListStore *store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_UINT);
    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
    // *** //
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    g_signal_connect(selection, "changed", G_CALLBACK(change_topic), chat->textview);
    // *** //
    GtkWidget *scroll = gtk_scrolled_window_new ( NULL, NULL );
    gtk_widget_set_size_request ( scroll, 200, 150 );
    gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scroll ), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );
    gtk_container_add ( GTK_CONTAINER ( scroll ), list );
    gtk_box_pack_start(GTK_BOX(gbox), scroll, TRUE, TRUE, 0);
    g_object_unref(store);
    // *** //
    GtkWidget *xbox = gtk_box_new ( GTK_ORIENTATION_HORIZONTAL, 0 );
    gtk_box_pack_start ( GTK_BOX ( xbox ), vbox, FALSE, TRUE, 0 );
    gtk_box_pack_start ( GTK_BOX ( xbox ), gbox, FALSE, TRUE, 1 );
    gtk_container_add ( GTK_CONTAINER ( window ), xbox );
    // *** //

    topics = load_topics( "topics.json" );
    
    if ( topics.size() > 0 ) {
        store = GTK_LIST_STORE(gtk_tree_view_get_model ( GTK_TREE_VIEW(list) ) );
        GtkTreeIter iter;
        for (size_t i = 0; i < topics.size(); i++) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, LIST_ITEM, (gchar *)topics[i].topic.en.c_str(), LIST_INDEX, (guint)i, -1);
        }
        initBotMessage( chat->textview, (gchar *)"Welcome back sir, please select topic to learning.");
    } 

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
    if (topic.items.size() == 0) {
        gtk_text_buffer_insert_with_tags_by_name ( buffer, &iter, "Please select topic!", -1, "italic", "red_fg", NULL );
    } else {
        std::string en = toLowerCase(topic.items[current_index].en);
        std::string ip = toLowerCase(std::string(g_strdup(text)));
        if (ip == en) {
            gtk_text_buffer_insert_with_tags_by_name ( buffer, &iter, "Good job.", -1, "italic", "blue_fg", NULL );
            current_index = m_rand(0, topic.items.size() - 1);
            initBotMessage(GTK_WIDGET(chat->textview), (gchar *)topic.items[current_index].vi.c_str());
            hint = m_rand(3,5);
            trying = 0;
        } else {
            gtk_text_buffer_insert_with_tags_by_name ( buffer, &iter, "Oh No.", -1, "italic", "red_fg", NULL );
            if (trying > hint) {
                initBotMessage(GTK_WIDGET(chat->textview), (gchar *)topic.items[current_index].en.c_str());
                trying = 0;
            }
            trying++;
        }
    }
    gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW ( chat->textview ), mark);

    gtk_entry_set_text ( GTK_ENTRY ( chat->entry ), "" );
}
void change_topic(GtkWidget *listview, gpointer view) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *value;
    guint index;
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(listview), &model, &iter)) {
        gtk_tree_model_get(model, &iter, LIST_ITEM, &value, LIST_INDEX, &index,  -1);
        initBotMessage(GTK_WIDGET(view), g_strdup_printf("Topic changed to \"%s\"", value));
        topic = topics[(unsigned int)index];
        current_index = m_rand(0, topic.items.size() - 1);
        initBotMessage(GTK_WIDGET(view), (gchar *)topic.items[current_index].vi.c_str());
        g_free(value);
    }
}
void initBotMessage( GtkWidget *view, gchar *message ) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( view ) );
    GtkTextMark *mark = gtk_text_buffer_get_insert ( buffer );
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark ( buffer, &iter, mark );
    if ( gtk_text_buffer_get_char_count ( buffer ) > 0 ) {
        gtk_text_buffer_insert ( buffer, &iter, "\n", -1 );
    }
    gtk_text_buffer_insert_with_tags_by_name(buffer, &iter,"Bot: ", -1, "gap", "red_fg", "bold",  NULL);
    gtk_text_buffer_insert_with_tags_by_name ( buffer, &iter, message, -1, "italic", "gray_fg", NULL );
    gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW ( view ), mark);
}
std::vector<topic_t> load_topics( std::string filepath ) {
    std::vector<topic_t> _topics;
    if ( ! file_exists (filepath) ) return _topics;
    std::string js = load_json_file( filepath );
    if ( js.size() <= 0 ) {
        return _topics;
    }
    json::JSON obj;
    try {
        obj = json::JSON::Load( js );
    } catch(...) {
        return _topics;
    }
    if (obj.IsNull()) return _topics;
    if (obj.JSONType() != json::JSON::Class::Array) return _topics;
    for(auto it : obj.ArrayRange()) {
        if (it.JSONType() != json::JSON::Class::Object) continue;
        if (!it.hasKey("en") || !it.hasKey("vi") || !it.hasKey("data")) continue;
        if (it["en"].JSONType() != json::JSON::Class::String) continue;
        if (it["vi"].JSONType() != json::JSON::Class::String) continue;
        if (it["data"].JSONType() != json::JSON::Class::Array) continue;
        topic_t topic;
        topic.topic = {
            .en = it["en"].ToString(),
            .vi = it["vi"].ToString()
        };
        for(auto mt : it["data"].ArrayRange()) {
            if (mt.JSONType() != json::JSON::Class::Object) continue;
            if (!mt.hasKey("en") || !mt.hasKey("vi")) continue;
            item_t item = {
                .en = mt["en"].ToString(),
                .vi = mt["vi"].ToString()
            };
            topic.items.push_back(item);
        }
        _topics.push_back(topic);
    }
    return _topics;
}
std::string toLowerCase(std::string s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){
        return std::tolower(c);
    });
    return result;
}
