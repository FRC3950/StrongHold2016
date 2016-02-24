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
	//while(acquireImaq) {
		IMAQdxGrab(session, frame, true, NULL);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
		} else {
//			imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
			// filter out red and blue
			Range redRange;
			redRange.minValue = 0;
			redRange.minValue = 255;
			Range greenRange;
			greenRange.minValue = 0;
			greenRange.minValue = 255;
			Range blueRange;
			blueRange.minValue = 0;
			blueRange.minValue = 255;
//			Image * frame1 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
			imaqColorThreshold(frame, frame, 255, ColorMode::IMAQ_RGB, &redRange, &greenRange, &blueRange);

			//	        imaqSizeFilter(frame, frame, Connectivity::IMAQ_EIGHT_CONNECTED, 1, IMAQ_KEEP_LARGE, NULL);

			// filter out particles that are less than 45 pixels in width
			ParticleFilterCriteria criteria = ParticleFilterCriteria();
			criteria.parameter = MeasurementValue::IMAQ_WIDTH;
			criteria.exclude = false;
			criteria.lower = 0.0;
			criteria.upper = 45.0;
			//imaqParticleFilter(frame, frame, &criteria, 1, false, Connectivity::IMAQ_EIGHT_CONNECTED);

			// create bounding boxes for remaining particles
			//imaqConvexHull(frame, frame, Connectivity::IMAQ_EIGHT_CONNECTED);

			//			imaqParticleFilter4(Image* dest, Image* source,
			//			                    const ParticleFilterCriteria2* criteria, int criteriaCount,
			//			                    const ParticleFilterOptions2* options, const ROI* roi,
			//			                    int* numParticles);
			//			imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
			CameraServer::GetInstance()->SetImage(frame);
		}
		//Wait(0.005);				// wait for a motor update time
	//}
}

void VisionSubsystem::Off()
{
	acquireImaq = false;
	//DriverStation::ReportError("I am in VisionSubsystem::Off()\n");

    // stop image acquisition
	IMAQdxStopAcquisition(session);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
