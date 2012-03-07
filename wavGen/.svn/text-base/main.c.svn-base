/*
 * waveGen.c
 *
 *  Created on: Aug 19, 2010
 *      Author: Lucas Campbell
 */
/**
 * @file main.c
 * @author Luke Campbell
 * @brief contains int main()
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





/* Only purpose of main() is to allocate resources and then init the app */
/**
 * It's main()
 */
int main(int argc, char *argv[])
{
	MainWindow *app;
	GtkBuilder *builder;
	GError *error = NULL;
	gtk_init(&argc,&argv);
	app = g_slice_new(MainWindow);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder,"template.xml",&error);
	if(error) {
		g_error("%s",error->message);
		g_error_free(error);
		g_slice_free(MainWindow,app);
		return 1;
	}
	app->channel1 = g_slice_new(Waveform);
	app->channel2 = g_slice_new(Waveform);
	setWidgets(app,builder);
	connectSignals(app,builder);



	gtk_widget_show(app->window1);
	gtk_main();
	g_slice_free(MainWindow,app);

	g_slice_free(Waveform,app->channel1);
	g_slice_free(Waveform,app->channel2);

	return 0;
}
