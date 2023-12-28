#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include<stdbool.h>  
#include <cairo.h>
#include "math.h"
list* tete=NULL;
GObject *drawing_area;
static gboolean should_draw = FALSE;
//structure pour les deux data pointers
typedef struct {
    gpointer data1;
    gpointer data2;
} TwoDataPointers;

//fonctions pour le dessin
static void
draw_function (GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data) {
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); 
  cairo_paint(cr);

if (should_draw) {
    list* current = tete;
    int MaxnumCircles = 10;
    int numCircles = 0;
    double centerX = width / 2.0;
    double centerY = height / 2.0;
    double radius = 35;
    double separation = 30;


    cairo_set_line_width(cr, 2);
    cairo_set_source_rgb(cr, 0, 0, 0);

    // dessin des cercles et des lignes
   for (int i = 0; i < MaxnumCircles && current != NULL; ++i, current = current->suivant) {
        double x = centerX + (radius * 2 + separation) * (i - (MaxnumCircles - 1) / 2.0);
        double y = centerY;

        // dessin des cercles 
        cairo_arc(cr, x, y, radius, 0, 2 * M_PI);
        cairo_stroke(cr);

        // dessin des nombres dans les cercles
        char number[3];
        sprintf(number, "%d", current->element);
        cairo_text_extents_t text_extents;
        cairo_set_font_size(cr, 20);
        cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_text_extents(cr, number, &text_extents);
        cairo_move_to(cr, x - text_extents.width / 2, y + text_extents.height / 2);
        cairo_show_text(cr, number);
        numCircles++;
        // dessin des lignes entre les cercles
      if (i < MaxnumCircles - 1 && current->suivant != NULL) {
        double nextX = centerX + (radius * 2 + separation) * ((i + 1) - (MaxnumCircles - 1) / 2.0);
        double nextY = centerY;
        cairo_move_to(cr, x + radius, y);
        cairo_line_to(cr, nextX - radius, nextY);
        cairo_stroke(cr);
      }
    }
  }
}

static void
button_clicked(GtkButton *button, gpointer data) {
  should_draw = TRUE; // Set to TRUE when the button is clicked
  gtk_widget_queue_draw(GTK_WIDGET(data)); 
}




//fonction pour la creation
static void creation(GtkWidget *widget, gpointer data) {
    int count = 0;
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(data));
    char *token = strtok((char *)text, ",");
    MathCreer(&tete, token, count);
    afficherlist(tete);
}


//fonction pour l'insertion
static void insertion (GtkWidget *widget,TwoDataPointers   *datap){  
    const gchar *text1 = gtk_editable_get_text(GTK_EDITABLE(datap->data1));
    const gchar *text2 = gtk_editable_get_text(GTK_EDITABLE(datap->data2));
    MathAdd(&tete, atoi(text1),atoi(text2)) ;  afficherlist(tete); 
  }


//fonction pour la suppression
static void suppression (GtkWidget *widget,gpointer   data){ 
  const gchar *text = gtk_editable_get_text(GTK_EDITABLE(data));
  MathSupp(&tete, atoi(text)); afficherlist(tete);

}


//fonction pour la recherche
static void recherche (GtkWidget *widget,gpointer   data){ 
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(data));
    if ( MathSearch(tete, atoi(text)) == true) {  
      gtk_widget_add_css_class(GTK_WIDGET(data), "found");
      gtk_widget_remove_css_class(GTK_WIDGET(data), "error");

    }
    else {
      gtk_widget_remove_css_class(GTK_WIDGET(data), "found");
      gtk_widget_add_css_class(GTK_WIDGET(data), "error");
    }
}

//fonction pour le tri
static void tri (GtkWidget *widget,gpointer   data){
    MathBubbleSort(&tete); afficherlist(tete);
}

//fonction pour changer la visibilité d'un widget
void reveal (GtkWidget *widget,gpointer   data){ 
  gboolean visible = gtk_widget_get_visible(GTK_WIDGET(data));
  if (visible) gtk_widget_set_visible(GTK_WIDGET(data), FALSE);
    else gtk_widget_set_visible(GTK_WIDGET(data), TRUE);   
        }


//fonction pour l'interface
static void activate (GtkApplication *app, gpointer user_data){

//declaration des variables
GObject *window;
GObject *grid;
GObject *button;
GObject *entry;
GObject *entry1;
GObject *GoButton;
GtkCssProvider *cssProvider = gtk_css_provider_new();
TwoDataPointers *datap = g_new(TwoDataPointers, 1);

  // initialisation du gtk builder
  GtkBuilder *builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "builder.ui.xml", NULL);

  // creation de la fenetre
  window = gtk_builder_get_object (builder, "window");
  gtk_window_set_application (GTK_WINDOW (window), app);
  /*------------------CSS-------------------------------*/
const char cssPath[] = "style.css";
gtk_css_provider_load_from_path(cssProvider, cssPath);
gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
/*******************************************************/

  //creation du grid
  grid = gtk_builder_get_object (builder, "grid");

//drawing area
  drawing_area = gtk_builder_get_object(builder, "animations");
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_function, NULL, NULL);

  //button 1 creation
  button = gtk_builder_get_object (builder, "buttonCreate");
    //entry valeurs
    entry = gtk_builder_get_object (builder, "EntryCreate");
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
    gtk_widget_add_css_class(GTK_WIDGET(entry), "noerror");
    //go button
      GoButton = gtk_builder_get_object (builder, "buttonGoCreate");
      gtk_widget_set_visible(GTK_WIDGET(GoButton), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), GoButton);
      g_signal_connect (GoButton, "clicked", G_CALLBACK (creation), entry);
      g_signal_connect (GoButton, "clicked", G_CALLBACK(button_clicked), drawing_area);

  //button 2 insertion
    button = gtk_builder_get_object (builder, "buttonInsert");
      //entry 1 valeur
      entry1 = gtk_builder_get_object (builder, "EntryValInsert");
      gtk_widget_set_visible(GTK_WIDGET(entry1), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry1);
      gtk_widget_add_css_class(GTK_WIDGET(entry1), "noerror");
      datap->data1 = entry1;
      //entry 2 position
      entry = gtk_builder_get_object (builder, "EntryPosInsert");
      gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
      gtk_widget_add_css_class(GTK_WIDGET(entry), "noerror");
      datap->data2 = entry;
      //go button
      GoButton = gtk_builder_get_object (builder, "buttonGoInsert");
      gtk_widget_set_visible(GTK_WIDGET(GoButton), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), GoButton);
      g_signal_connect (GoButton, "clicked", G_CALLBACK (insertion), datap);
      g_signal_connect (GoButton, "clicked", G_CALLBACK(button_clicked), drawing_area);


  //button 3 suppresion
  button = gtk_builder_get_object (builder, "buttonRemove");
    //entry position
    entry = gtk_builder_get_object (builder, "EntryPosSupp");
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
    gtk_widget_add_css_class(GTK_WIDGET(entry), "noerror");
    //go button
      GoButton = gtk_builder_get_object (builder, "buttonGoSupp");
      gtk_widget_set_visible(GTK_WIDGET(GoButton), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), GoButton);
      g_signal_connect (GoButton, "clicked", G_CALLBACK (suppression), entry);
      g_signal_connect (GoButton, "clicked", G_CALLBACK(button_clicked), drawing_area);

  //button 4 recherche
  button = gtk_builder_get_object (builder, "buttonSearch");
    //entry valeur
    entry = gtk_builder_get_object (builder, "EntryValSearch");
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
    gtk_widget_add_css_class(GTK_WIDGET(entry), "noerror");

    //go button
      GoButton = gtk_builder_get_object (builder, "buttonGoSearch");
      gtk_widget_set_visible(GTK_WIDGET(GoButton), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), GoButton);
      g_signal_connect (GoButton, "clicked", G_CALLBACK (recherche), entry);

  

  //button 5 tri
  button = gtk_builder_get_object (builder, "buttonSort");
  g_signal_connect(button, "clicked", G_CALLBACK(tri), NULL);
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), drawing_area);
  

  //button 7 quitter
  button = gtk_builder_get_object (builder, "buttonQuit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);
  //gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(button), 4, 4, 4, 4);






//gtk_window_fullscreen(GTK_WINDOW(window));
  // affichage de la fenetre
  gtk_widget_set_visible (GTK_WIDGET (window), TRUE);
  // on a plus besoin du builder
  g_object_unref (builder);
}


//fonction main
int main (int   argc,char *argv[]){


  GtkApplication *app = gtk_application_new ("project.Algo", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
