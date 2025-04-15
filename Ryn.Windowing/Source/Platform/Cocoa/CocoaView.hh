#pragma once

#include <Ryn/Windowing/Input/Key.hpp>
#include <Ryn/Windowing/Input/MouseButton.hpp>

#include "CocoaWindow.hh"

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>

@interface CocoaView : NSView
{
    Ryn::CocoaWindow* cocoaWindow;
    NSTrackingArea* trackingArea;
    CAMetalLayer* metalLayer;
}

- (instancetype)initWithWindow:(Ryn::CocoaWindow*)window;
- (void)dealloc;
- (BOOL)acceptsFirstResponder;
- (BOOL)canBecomeKeyView;
- (BOOL)wantsUpdateLayer;
- (void)updateTrackingAreas;
- (void)viewDidChangeBackingProperties;
- (void)keyDown:(NSEvent*)event;
- (void)keyUp:(NSEvent*)event;
- (void)flagsChanged:(NSEvent*)event;
- (void)mouseMoved:(NSEvent*)event;
- (void)scrollWheel:(NSEvent*)event;
- (void)mouseDown:(NSEvent*)event;
- (void)mouseUp:(NSEvent*)event;
- (void)rightMouseDown:(NSEvent*)event;
- (void)rightMouseUp:(NSEvent*)event;
- (void)otherMouseDown:(NSEvent*)event;
- (void)otherMouseUp:(NSEvent*)event;

@end

Ryn::Key MapCocoaKey(UInt16 keycode);
Ryn::MouseButton MapCocoaMouseButton(NSInteger button);
