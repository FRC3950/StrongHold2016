#include "VisionSubsystem.h"
#include "../RobotMap.h"

VisionSubsystem::VisionSubsystem() :
		Subsystem("VisionSubsystem")
{
	acquireImaq = false;

    // create an image
	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	//the camera name (ex "cam0") can be found through the roborio web interface
	imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
	}
	imaqError = IMAQdxConfigureGrab(session);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxConfigureGrab error: " + std::to_string((long)imaqError) + "\n");
	}

}

void VisionSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void VisionSubsystem::On()
{
    // acquire images
	IMAQdxStartAcquisition(session);

	acquireImaq = true;

    // grab an image, draw the circle, and provide it for the camera server which will
    // in turn send it to the dashboard.
//	while(acquireImaq) {
		IMAQdxGrab(session, frame, true, NULL);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
		} else {
//			imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
			CameraServer::GetInstance()->SetImage(frame);
		}
//		Wait(0.005);				// wait for a motor update time
//	}
}

void VisionSubsystem::Off()
{
	acquireImaq = false;
	DriverStation::ReportError("I am in VisionSubsystem::Off()\n");

    // stop image acquisition
	IMAQdxStopAcquisition(session);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
