/* GStreamer
 * Copyright (C) 1999,2000 Erik Walthinsen <omega@cse.ogi.edu>
 *                    2005 Wim Taymans <wim@fluendo.com>
 *
 * gstaudiosrc.h: 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/* a base class for simple audio srcs.
 *
 * This base class only requires subclasses to implement a set
 * of simple functions.
 *
 * - open: open the device with the specified caps
 * - read: read samples to the audio device
 * - close: close the device
 * - delay: the number of samples queued in the device
 * - reset: unblock a read to the device and reset.
 *
 * All scheduling of samples and timestamps is done in this
 * base class.
 */

#ifndef __GST_AUDIOSRC_H__
#define __GST_AUDIOSRC_H__

#include <gst/gst.h>
#include <gst/audio/gstbaseaudiosrc.h>

G_BEGIN_DECLS

#define GST_TYPE_AUDIOSRC  	 	(gst_audiosrc_get_type())
#define GST_AUDIOSRC(obj) 	 	(G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_AUDIOSRC,GstAudioSrc))
#define GST_AUDIOSRC_CLASS(klass) 	(G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_AUDIOSRC,GstAudioSrcClass))
#define GST_AUDIOSRC_GET_CLASS(obj) 	(G_TYPE_INSTANCE_GET_CLASS ((obj),GST_TYPE_AUDIOSRC,GstAudioSrcClass))
#define GST_IS_AUDIOSRC(obj)  	 	(G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_AUDIOSRC))
#define GST_IS_AUDIOSRC_CLASS(obj)	(G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_AUDIOSRC))

typedef struct _GstAudioSrc GstAudioSrc;
typedef struct _GstAudioSrcClass GstAudioSrcClass;

struct _GstAudioSrc {
  GstBaseAudioSrc 	 element;

  /*< private >*/ /* with LOCK */
  GThread   *thread;
};

struct _GstAudioSrcClass {
  GstBaseAudioSrcClass parent_class;

  /* vtable */

  /* open the device with given specs */
  gboolean (*open)   (GstAudioSrc *src, GstRingBufferSpec *spec);
  /* close the device */
  gboolean (*close)  (GstAudioSrc *src);
  /* read samples from the device */
  guint    (*read)   (GstAudioSrc *src, gpointer data, guint length);
  /* get number of samples queued in the device */
  guint    (*delay)  (GstAudioSrc *src);
  /* reset the audio device, unblock from a write */
  void     (*reset)  (GstAudioSrc *src);
};

GType gst_audiosrc_get_type(void);

G_END_DECLS

#endif /* __GST_AUDIOSRC_H__ */
