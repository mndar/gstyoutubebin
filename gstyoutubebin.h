#ifndef _youtubebin_h_
#define _youtubebin_h_
#include <glib.h>
#include <glib-object.h>
#include <gst/gst.h>
#include <gst/gstbin.h>
#include <gio/gio.h>
#ifndef DEBUG
#define DEBUG g_message ("HERE File:%s Line:%d", __FILE__, __LINE__);
#endif

G_BEGIN_DECLS
enum
{
  YOUTUBE_PROP_URI=1,
  YOUTUBE_N_PROPERTIES
};

static GParamSpec *youtube_bin_properties[YOUTUBE_N_PROPERTIES] = { NULL, };

G_DECLARE_FINAL_TYPE(GstYoutubeBin, youtubebin, GST_YOUTUBE, BIN, GstBin)

#define GST_TYPE_YOUTUBE_BIN (gst_youtube_bin_get_type ())

GstYoutubeBin *youtubebin_new ();
GType ges_youtube_bin_get_type (void);

typedef struct _GstYoutubeBin {
	GstBin parent_instance;
	gchar *uri;
	GstElement *youtube_iostream;
}GstYoutubeBin;
G_END_DECLS
#endif

