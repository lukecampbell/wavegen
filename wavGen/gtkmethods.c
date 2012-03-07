/*
 * gtkmethods.c
 *
 *  Created on: Jan 1, 2011
 *      Author: luke
 */
/**
 * @file gtkmethods.c
 * @author Luke Campbell
 * @brief Source for functions for the GUI
 * @date 3/12/2011
 */
#include <riff2_pcm.h>
#include <riff2.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "waveGen.h"
#include "gtkradio.h"

#define GETWIDGET(yy,xx) \
	yy->xx = GTK_WIDGET(gtk_builder_get_object(builder,#xx))
#define ENTTEXT(xx) \
	gtk_entry_get_text(GTK_ENTRY(xx))
/* bring up a quick dialog with label of message */
/**
 * Displays a dialog with a message to the user.
 * @param parent The parent widget
 * @param message The message to be displayed
 */
void
quick_message(GtkWidget *parent, gchar *message)
{
	GtkWidget *dialog, *label, *content_area;
	dialog = gtk_dialog_new_with_buttons("Message",GTK_WINDOW(parent),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_STOCK_OK,
			GTK_RESPONSE_NONE,
			NULL);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	label = gtk_label_new(message);
	gtk_container_add(GTK_CONTAINER(content_area),label);
	g_signal_connect_swapped(dialog,"response",G_CALLBACK(gtk_widget_destroy),dialog);
	gtk_widget_show_all(dialog);
}
/* displays a dialog prompting for 3 values (frequencies) */
/**
 * Displays a dialog prompting the user for 3 values
 * @param parent The parent widget
 * @param wf The waveform struct to be modified by the three frequencies
 */
void
trifreq_prompt(GtkWidget *parent,Waveform *wf)
{
	gint response;
	const gchar *buf;
	GtkWidget *dialog, *label, *vbox, *content_area, *entry1, *entry2, *entry3;
	dialog = gtk_dialog_new_with_buttons("Enter Frequencies",GTK_WINDOW(parent),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,
			GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
			NULL);
	/* build widgets */
	label = gtk_label_new("Please enter the three frequencies:");
	vbox = gtk_vbox_new(TRUE,0);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	entry1 = gtk_entry_new();
	entry2 = gtk_entry_new();
	entry3 = gtk_entry_new();
	/********************/

	/* packing and building the content pane */
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),entry1,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),entry2,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),entry3,FALSE,FALSE,0);
	gtk_container_add(GTK_CONTAINER(content_area),vbox);
	gtk_widget_show_all(dialog);
	/********************/

	response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_ACCEPT) //Handle user input
	  {
		buf = ENTTEXT(entry1);
		if(buf!=NULL)
			wf->lfm.freq1 = g_strtod(buf,NULL);
		else
			wf->lfm.freq1 = 0;
#ifdef __DEBUG__
		g_printf("DEBUG: Freq1: %f\n",wf->lfm.freq1);
#endif
		buf = ENTTEXT(entry2);
		if(buf!=NULL)
			wf->lfm.freq2 = g_strtod(buf,NULL);
		else
			wf->lfm.freq2 = 0;
#ifdef __DEBUG__
		g_printf("DEBUG: Freq2: %f\n",wf->lfm.freq2);
#endif
		buf = ENTTEXT(entry3);
		if(buf!=NULL)
			wf->lfm.freq3 = g_strtod(buf,NULL);
		else
			wf->lfm.freq3 = 0;
#ifdef __DEBUG__
		g_printf("DEBUG: Freq3: %f\n",wf->lfm.freq3);
#endif
	  }
	else
	  {
		wf->lfm.freq1 = 0;
		wf->lfm.freq2 = 0;
		wf->lfm.freq3 = 0;
	  }
	gtk_widget_destroy(dialog);
}
/**
 * Displays a file-choosing dialog, you need to free the returned pointer
 * @warning You must free the pointer returned by this function
 * @param parent The parent GtkWidget
 * @return The string of the file-path, you must free the returned string
 */
char*
chooseFile(GtkWidget *parent)
{
	GtkWidget *dialog;
	char *filename;
	dialog = gtk_file_chooser_dialog_new("Save File",GTK_WINDOW(parent),
			GTK_FILE_CHOOSER_ACTION_SAVE,
			GTK_STOCK_SAVE,GTK_RESPONSE_ACCEPT,
			GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
			NULL);
	if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

	}
	else
		filename = NULL;
	gtk_widget_destroy(dialog);
	return filename;
}
/* This function is a big handler for everything and it needs to get segmented more */
/**
 * This function handles the entire window's signals
 * @param widget The parent GtkWidget
 * @param data The main GUI window (MainWindow)
 */
void
toggle(GtkWidget *widget, MainWindow *data)
{
	const gchar *buf;
	/* handle radio button selections */
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->radiobutton1)))
		data->channel1->form = SINE16;
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->radiobutton2)))
		data->channel1->form = STEPLFM16;
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->radiobutton3)))
		data->channel1->form = LFMWAVE16;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->radiobutton4)))
		data->channel2->form = SINE16;
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->radiobutton5)))
		data->channel2->form = STEPLFM16;
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->radiobutton6)))
		data->channel2->form = LFMWAVE16;
	/* if LFM is selected display prompt for the frequencies */
	if(data->channel1->form == STEPLFM16)
	  {
		trifreq_prompt(data->window1,data->channel1);
	  }
	if(data->channel2->form == STEPLFM16)
	  {
		trifreq_prompt(data->window1,data->channel2);
	  }
	/******************************/

	/* obtain frequencies from text_entry fields */
	buf = gtk_entry_get_text(GTK_ENTRY(data->entry1));
	if(buf!=NULL)
		data->channel1->freq = g_strtod(buf,NULL);
	else
		data->channel1->freq = 0;
	buf = gtk_entry_get_text(GTK_ENTRY(data->entry2));
	if(buf!=NULL)
		data->channel2->freq = g_strtod(buf,NULL);
	else
		data->channel2->freq = 0;
	/******************************/

	/* Get volume level from slider bar */
	data->channel1->volume = data->channel2->volume =
			gtk_range_get_value(GTK_RANGE(data->vscale1)) / 100;
	g_printf("Volume: %f\n",data->channel1->volume);
	/*******************************/
	/* Get channel 1 time */
	buf = gtk_entry_get_text(GTK_ENTRY(data->entry4));
	if(buf)
		data->channel1->time = g_strtod(buf,NULL);
	else
		data->channel2->time = 3;
	/*******************************/
	/* Get channel 2 time */
	buf = gtk_entry_get_text(GTK_ENTRY(data->entry5));
	if(buf)
		data->channel2->time = g_strtod(buf,NULL);
	else
		data->channel2->time = 3;
	/*******************************/
	/* Get Length of wav produced from text entry */
	buf = gtk_entry_get_text(GTK_ENTRY(data->entry3));
	if(buf)
		data->length = g_strtod(buf,NULL);
	else
		data->length = 3;
	/*******************************/
	
	data->filename = chooseFile(data->window1);


	if(data->filename)
	  {
#ifdef __DEBUG__
		g_printf("Filename: %s\n",data->filename);
#endif
		generate(data->filename,data->channel1,data->channel2,data->length);
		g_free(data->filename);
	  }
	else
		generate("./test.wav",data->channel1,data->channel2,data->length);


}
/**
 * Exits the application
 * @param widget The parent GtkWidget
 * @param data Should be a NULL pointer, has no importance
 */
void
endme(GtkWidget *widget, gpointer *data)
{
	gtk_main_quit();
}
/**
 * Initializes the Widgets
 * @param app The main window interface of type MainWindow
 * @param builder The GtkBuilder
 */
void
setWidgets(MainWindow *app,GtkBuilder *builder)
{
	GETWIDGET(app,window1);
	GETWIDGET(app,radiobutton1);
	GETWIDGET(app,radiobutton2);
	GETWIDGET(app,radiobutton3);
	GETWIDGET(app,button1);
	GETWIDGET(app,button2);
	GETWIDGET(app,vscale1);
	GETWIDGET(app,radiobutton4);
	GETWIDGET(app,radiobutton5);
	GETWIDGET(app,radiobutton6);
	GETWIDGET(app,entry1);
	GETWIDGET(app,entry2);
	GETWIDGET(app,entry3);
	GETWIDGET(app,entry4);
	GETWIDGET(app,entry5);
}
/**
 * Connects the signal handlers to the GUI
 * @param app The main window interface
 * @builder The GtkBuilder
 */
void
connectSignals(MainWindow *app,GtkBuilder *builder)
{
	g_signal_connect_swapped(app->button2,"clicked",G_CALLBACK(gtk_widget_destroy),app->window1);
	g_signal_connect(app->window1,"delete-event",G_CALLBACK(endme),NULL);
	g_signal_connect(app->window1,"destroy",G_CALLBACK(endme),NULL);
	g_signal_connect(app->button1,"clicked",G_CALLBACK(toggle),app);
	gtk_builder_connect_signals(builder,app->window1);

	gtk_range_set_value(GTK_RANGE(app->vscale1),15.0);
}
