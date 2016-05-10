#ifndef VisionSubsystem_H
#define VisionSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class VisionSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	IMAQdxSession session;
	Image * frame;
	IMAQdxError imaqError;
	bool acquireImaq;

public:
	VisionSubsystem();
	void InitDefaultCommand();
	void On();
	void Off();
	void GrabImage();

};

#endif
