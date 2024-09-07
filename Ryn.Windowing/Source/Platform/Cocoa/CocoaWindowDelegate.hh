#pragma once

#include "CocoaWindow.hh"

#import <Cocoa/Cocoa.h>

@interface CocoaWindowDelegate : NSObject <NSWindowDelegate>
{
    Ryn::CocoaWindow* cocoaWindow;
}

- (instancetype)initWithWindow:(Ryn::CocoaWindow*)window;
- (BOOL)windowShouldClose:(NSNotification*)notification;
- (void)windowDidMove:(NSNotification*)notification;
- (void)windowDidResize:(NSNotification*)notification;
- (void)windowDidBecomeKey:(NSNotification*)notification;
- (void)windowDidResignKey:(NSNotification*)notification;

@end
