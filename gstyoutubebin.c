#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "gstyoutubebin.h"

G_DEFINE_TYPE(GstYoutubeBin, gst_youtube_bin, GST_TYPE_BIN)

gboolean
gst_youtube_bin_add_element (GstBin *gstbin, GstElement *element) {
	g_message ("GstYoutubeBin Element Add");
	GstYoutubeBin *bin = (GstYoutubeBin *) gstbin;	
	GError *error = NULL;
	GSubprocess *youtube_dl = g_subprocess_new (G_SUBPROCESS_FLAGS_STDOUT_PIPE, &error, "/usr/bin/youtube-dl", bin->uri, "-o", "-", NULL);
	if (error) {
		g_error ("Could Not Launch Sub-Proess youtube-dl");
	}
	GInputStream *istream = g_subprocess_get_stdout_pipe (youtube_dl);
	g_object_set (element, "stream", istream, NULL);
	GstPad *data_src_pad = gst_element_get_static_pad (element, "src");
	gst_element_add_pad ((GstElement *) bin, gst_ghost_pad_new ("src", data_src_pad));
	gst_element_set_state (element, GST_STATE_PLAYING);
	return TRUE;
}

static void
gst_youtube_bin_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
	GstYoutubeBin *self = (GstYoutubeBin *) object;
	GError *error = NULL;
	switch (property_id) {
		case YOUTUBE_PROP_URI:
			self->uri = g_value_dup_string (value);
			self->youtube_iostream = gst_element_factory_make ("giostreamsrc", "giostreamsrc");
			if (error) {
				g_error ("GioStreamSrc Error Code:%d Message:%s", error->code, error->message);
			}
			gst_youtube_bin_add_element ((GstBin *) self, self->youtube_iostream);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

void
gst_youtube_bin_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
}


//Virt funcs overrides, properties, signal defs here
static void
gst_youtube_bin_class_init (GstYoutubeBinClass *klass) {
  GstBinClass *object_class = GST_BIN_CLASS (klass);
  object_class->add_element = gst_youtube_bin_add_element;
  
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->set_property = gst_youtube_bin_set_property;
  gobject_class->get_property = gst_youtube_bin_get_property;
  youtube_bin_properties[YOUTUBE_PROP_URI] = g_param_spec_string ("uri", "uri", "uri", NULL, G_PARAM_READWRITE);
  g_object_class_install_properties (gobject_class, YOUTUBE_N_PROPERTIES, youtube_bin_properties);
}

void
gst_youtube_bin_init (GstYoutubeBin *bin) {
	g_message ("GstYoutubeBin Init");
}

static gboolean
plugin_init (GstPlugin * plugin)
{
  return gst_element_register (plugin, "youtubebin", GST_RANK_NONE, \
                               GST_TYPE_YOUTUBE_BIN);
}

#ifndef VERSION
#define VERSION "0.0.1"
#endif
#ifndef PACKAGE
#define PACKAGE "YoutubeBin"
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME "YoutubeBinPack"
#endif
#ifndef GST_PACKAGE_ORIGIN
#define GST_PACKAGE_ORIGIN " "
#endif

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    youtubebin,
    "YoutubeBin",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)
