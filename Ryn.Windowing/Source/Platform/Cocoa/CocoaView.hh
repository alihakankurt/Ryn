#pragma once

#include <Ryn/Windowing/Input/Key.hpp>
#include <Ryn/Windowing/Input/MouseButton.hpp>
#include <Ryn/Windowing/Input/ModifierFlags.hpp>

#include "CocoaWindow.hh"

#import <Cocoa/Cocoa.h>

@interface CocoaView : NSView
{
    Ryn::CocoaWindow* cocoaWindow;
    NSTrackingArea* trackingArea;
}

- (instancetype)initWithWindow:(Ryn::CocoaWindow*)window;
- (void)dealloc;
- (BOOL)acceptsFirstResponder;
- (BOOL)canBecomeKeyView;
- (void)updateTrackingAreas;
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

Ryn::ModifierFlags MapCocoaModifierFlags(NSEventModifierFlags modifiers);
Ryn::Key MapCocoaKey(UInt16 keycode);
Ryn::MouseButton MapCocoaMouseButton(NSInteger button);
