// $Id$

#ifndef SIMPLE3XSCALER_HH
#define SIMPLE3XSCALER_HH

#include "Scaler3.hh"
#include "PixelOperations.hh"
#include "Scanline.hh"

namespace openmsx {

class RenderSettings;

template <class Pixel>
class Simple3xScaler : public Scaler3<Pixel>
{
public:
	Simple3xScaler(SDL_PixelFormat* format,
	               const RenderSettings& renderSettings);

	virtual void scaleBlank1to3(
		FrameSource& src, unsigned srcStartY, unsigned srcEndY,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scaleBlank2to3(
		FrameSource& src, unsigned srcStartY, unsigned srcEndY,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale2x1to9x3(FrameSource& src,
		unsigned srcstarty, unsigned srcendy, unsigned srcwidth,
		OutputSurface& dst, unsigned dststarty, unsigned dstendy);
	virtual void scale2x2to9x3(FrameSource& src,
		unsigned srcstarty, unsigned srcendy, unsigned srcwidth,
		OutputSurface& dst, unsigned dststarty, unsigned dstendy);
	virtual void scale1x1to3x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale1x2to3x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale4x1to9x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale4x2to9x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale2x1to3x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale2x2to3x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale8x1to9x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale8x2to9x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale4x1to3x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);
	virtual void scale4x2to3x3(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY);

private:
	template <typename ScaleOp> void doScale1(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY,
		ScaleOp scale);
	template <typename ScaleOp> void doScale2(FrameSource& src,
		unsigned srcStartY, unsigned srcEndY, unsigned srcWidth,
		OutputSurface& dst, unsigned dstStartY, unsigned dstEndY,
		ScaleOp scale);
	PixelOperations<Pixel> pixelOps;
	Scanline<Pixel> scanline;
	const RenderSettings& settings;
};

} // namespace openmsx

#endif
