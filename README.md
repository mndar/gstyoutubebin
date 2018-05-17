# gstyoutubebin
GST_PLUGIN_PATH=. gst-launch-1.0 youtubebin uri="https://www.youtube.com/watch?v=jDn2bn7_YSM" ! decodebin name=demux demux. ! audioconvert ! alsasink demux. ! videoconvert ! xvimagesink
