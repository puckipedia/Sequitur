/* GlNodeVisual.h
 * Copyright (c)2004 by Eric Hackborn.
 * All rights reserved.
 *
 * This code is not public domain, nor freely distributable.
 * Please direct any questions or requests to Eric Hackborn,
 * at <hackborn@angryredplanet.com>.
 *
 * ----------------------------------------------------------------------
 *
 * Known Bugs
 * ~~~~~~~~~~
 *	- None!  Ha ha!
 *
 * ----------------------------------------------------------------------
 *
 * History
 * ~~~~~~~
 * 2004.02.24			hackborn@angryredplanet.com
 * Created this file
 */
#ifndef GLPUBLIC_GLNODEVISUAL_H
#define GLPUBLIC_GLNODEVISUAL_H

#include <be/support/SupportDefs.h>
#include <GlPublic/GlRootRef.h>
class GlNode;
class GlRootNode;
class ArpBitmap;

/***************************************************************************
 * GL-NODE-VISUAL
 * I am an object generated by a node used to display that node's visual,
 * such as a LFO-style picture for a sine wave.
 ****************************************************************************/
class GlNodeVisual
{
public:
	virtual ~GlNodeVisual();

	/* Notification of a change.
	 */
	virtual void			ParamChanged(gl_param_key key);
	/* Generate a bitmap with the given dimensions and place it in outBm.
	 * Some clients might have multiple views they generate, so index can
	 * be used to step through them.  By default, this method locks my
	 * node and calls LockedVisual().
	 */
	virtual status_t		Visual(	int32 w, int32 h, ArpBitmap** outBm,
									int32 index = 0);

protected:
	GlNodeVisual(const GlRootRef& ref, gl_node_id nid);
	GlRootRef				mRef;
	gl_node_id				mNid;

	virtual status_t		PreVisual(GlNode* node);
	virtual status_t		LockedVisual(	GlNode* node, int32 w, int32 h,
											ArpBitmap** outBm, int32 index);
	virtual void			PostVisual(GlNode* node);

	/* The node is cached the first time it's found, for performance.
	 * These are convenience calls for locking the ref, caching or
	 * just returning the node, and unlocking the ref.
	 */
	GlNode*					LockNode();
	void					UnlockNode(GlNode* n);

private:
	GlNode*					mNode;
	GlRootNode*				mRoot;
};

#endif
