/*
 * gtkradio.h
 *
 *  Created on: Jan 1, 2011
 *      Author: luke
 */

#ifndef GTKRADIO_H_
#define GTKRADIO_H_

#include <gtk/gtk.h>
#include <glib.h>
#include <glib-object.h>
#include <glib/gprintf.h>
#include "waveGen.h"


typedef struct {
	GtkWidget *window1;
	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *radiobutton1;
	GtkWidget *radiobutton2;
	GtkWidget *radiobutton3;
	GtkWidget *vscale1;
	GtkWidget *radiobutton4;
	GtkWidget *radiobutton5;
	GtkWidget *radiobutton6;
	GtkWidget *entry1;
	GtkWidget *entry2;
	GtkWidget *entry3;
	GtkWidget *entry4;
	GtkWidget *entry5;
	Waveform *channel1;
	Waveform *channel2;
	char *filename;
	double length;
}MainWindow;

void quick_message(GtkWidget *parent, gchar *message);
void trifreq_prompt(GtkWidget *parent,Waveform *wf);
char *chooseFile(GtkWidget *parent);
void endme(GtkWidget *widget, gpointer *data);
void toggle(GtkWidget *widget, MainWindow *data);
void setWidgets(MainWindow *app,GtkBuilder *builder);
void connectSignals(MainWindow *app,GtkBuilder *builder);

#endif /* GTKRADIO_H_ */
