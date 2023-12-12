#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "math.h"
list* tete=NULL;
const gchar *text;
GObject *entry;

//fonctions pour les buttons
static void creating (GtkWidget *widget,gpointer   data){ g_print ("creation d'une liste chainée\n");}
static void adding (GtkWidget *widget,gpointer   data){    add(&tete, atoi(text),0) ;  afficherlist(tete); }
static void lire (GtkWidget *widget,gpointer   data){  text = gtk_editable_get_text(GTK_EDITABLE(entry)); adding(widget,data);}
static void deleting (GtkWidget *widget,gpointer   data){  g_print ("suppresion d'un noeud\n");}
static void visibility (GtkWidget *widget,gpointer   data){ 
  gboolean visible = gtk_widget_get_visible(GTK_WIDGET(data));
  if (visible)
        gtk_widget_set_visible(GTK_WIDGET(data), FALSE);
    else
        gtk_widget_set_visible(GTK_WIDGET(data), TRUE);   
        }


//fonction pour l'interface
static void activate (GtkApplication *app, gpointer user_data){
GObject *window;
GObject *grid;
GObject *button;
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
  //button entry
  entry = gtk_builder_get_object (builder, "Entry");
  g_signal_connect (entry, "activate", G_CALLBACK (lire), NULL);
  gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
  //button 2 insertion
  button = gtk_builder_get_object (builder, "buttonInsert");
  g_signal_connect (button, "clicked", G_CALLBACK (visibility), entry);
  //button 3 suppresion
  button = gtk_builder_get_object (builder, "buttonRemove");
  g_signal_connect (button, "clicked", G_CALLBACK (deleting), NULL);
  //button 4 recherche
  button = gtk_builder_get_object (builder, "buttonSearch");
  g_signal_connect (button, "clicked", G_CALLBACK (creating), NULL);
  //button 5 tri
  button = gtk_builder_get_object (builder, "buttonSort");
  g_signal_connect (button, "clicked", G_CALLBACK (creating), NULL);
  //button 7 quitter
  button = gtk_builder_get_object (builder, "buttonQuit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);
 



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
