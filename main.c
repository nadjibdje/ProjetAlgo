#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "math.h"
list* tete=NULL;
const gchar *text;

static void
draw_function (GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
  int square_size = 40.0;

  cairo_set_source_rgb (cr, 1.0, 1.0, 1.0); /* white */
  cairo_paint (cr);
  cairo_set_line_width (cr, 2.0);
  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0); /* black */
  cairo_rectangle (cr,
                   width/2.0 - square_size/2,
                   height/2.0 - square_size/2,
                   square_size,
                   square_size);
  cairo_stroke (cr);
}


//fonctions pour les buttons
static void creating (GtkWidget *widget,gpointer   data){ g_print ("creation d'une liste chainée\n");}
static void adding (GtkWidget *widget,gpointer   data){ add(&tete, atoi(text),0) ;  afficherlist(tete); }

static void lire (GtkWidget *widget,gpointer   data){ text = gtk_editable_get_text(GTK_EDITABLE(data)); 
                                                      if (atoi(text) > 100) {gtk_widget_add_css_class(GTK_WIDGET(data), "error"); 
                                                                             gtk_widget_remove_css_class(GTK_WIDGET(data), "noerror");
                                                          }
                                                        else {
                                                              gtk_widget_remove_css_class(GTK_WIDGET(data), "error");
                                                              gtk_widget_add_css_class(GTK_WIDGET(data), "noerror");
                                                              adding(widget,data);
                                                               }
 }
static void deleting (GtkWidget *widget,gpointer   data){  g_print ("suppresion d'un noeud\n");}

//fonction pour changer la visibilité d'un widget
void reveal (GtkWidget *widget,gpointer   data){ 
  gboolean visible = gtk_widget_get_visible(GTK_WIDGET(data));
  if (visible) gtk_widget_set_visible(GTK_WIDGET(data), FALSE);
    else gtk_widget_set_visible(GTK_WIDGET(data), TRUE);   
        }


//fonction pour l'interface
static void activate (GtkApplication *app, gpointer user_data){


GObject *window;
GObject *grid;
GObject *button;
GObject *entry;
GObject *drawing_area;
GtkCssProvider *cssProvider = gtk_css_provider_new();


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



  //button 1 creation
  button = gtk_builder_get_object (builder, "buttonCreate");
  g_signal_connect (button, "clicked", G_CALLBACK (creating), NULL);
    //entry valeurs
    entry = gtk_builder_get_object (builder, "EntryCreate");
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
    gtk_widget_add_css_class(GTK_WIDGET(entry), "noerror");

    //go button
      entry = gtk_builder_get_object (builder, "buttonGoCreate");
      gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
  
  

  //button 2 insertion
    button = gtk_builder_get_object (builder, "buttonInsert");
      //entry 1 position
      entry = gtk_builder_get_object (builder, "EntryPosInsert");
      gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
      gtk_widget_add_css_class(GTK_WIDGET(entry), "noerror");
  
      //entry 2 valeur
      entry = gtk_builder_get_object (builder, "EntryValInsert");
      gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
      gtk_widget_add_css_class(GTK_WIDGET(entry), "noerror");
      
      //go button
      entry = gtk_builder_get_object (builder, "buttonGoInsert");
      gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
  /*g_signal_connect (entry, "activate", G_CALLBACK (lire), entry);*/
  






  //button 3 suppresion
  button = gtk_builder_get_object (builder, "buttonRemove");
  g_signal_connect (button, "clicked", G_CALLBACK (deleting), NULL);
    //entry position
    entry = gtk_builder_get_object (builder, "EntryPosSupp");
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
    gtk_widget_add_css_class(GTK_WIDGET(entry), "noerror");

    //go button
      entry = gtk_builder_get_object (builder, "buttonGoSupp");
      gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);



  //button 4 recherche
  button = gtk_builder_get_object (builder, "buttonSearch");
  g_signal_connect (button, "clicked", G_CALLBACK (creating), NULL);
    //entry valeur
    entry = gtk_builder_get_object (builder, "EntryValSearch");
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);
    gtk_widget_add_css_class(GTK_WIDGET(entry), "noerror");

    //go button
      entry = gtk_builder_get_object (builder, "buttonGoSearch");
      gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
      g_signal_connect (button, "clicked", G_CALLBACK (reveal), entry);



  //drawing area
  drawing_area = gtk_builder_get_object(builder, "animations");
  gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (drawing_area), draw_function, NULL, NULL);
  //gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA (drawing_area), draw_callback, NULL, NULL);
  //g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_callback), NULL);

  //button 5 tri
  button = gtk_builder_get_object (builder, "buttonSort");
  g_signal_connect(button, "clicked", G_CALLBACK(creating), drawing_area);
 
  
  //button 7 quitter
  button = gtk_builder_get_object (builder, "buttonQuit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(button), 4, 4, 4, 4);






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
