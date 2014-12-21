/** @file fileGrabber.h
 *
 * implementation - Grabber loads images from file
 *
 */

#ifndef FILE_GRABBER_H_INCLUDED
#define FILE_GRABBER_H_INCLUDED

#include "grabber.h"
#include "../include/Grabber/xtion_grabber.h"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <chrono>
#include <memory>

namespace putslam {
    /// create a single grabber (Generic Camera)
    Grabber* createGrabberFile(void);
    Grabber* createGrabberFile(std::string configFile);
};

using namespace putslam;

/// Grabber implementation
class FileGrabber : public Grabber {
    public:
        /// Pointer
        typedef std::unique_ptr<FileGrabber> Ptr;

        /// Construction
        FileGrabber(void);
        //FileGrabber(std::string modelFilename) : Grabber("Kinect Grabber", TYPE_PRIMESENSE), model(modelFilename){
        //      }

        /// Destructor
        ~FileGrabber(void);

        /// Grab image and/or point cloud
        bool grab();

        /// Set sequence properties
        void setSequence(const uint_fast32_t startFrameNo, const std::string& imagePrefix, const std::string& depthPrefix, const std::string& cloudPrefix);

        /// Grab sequence of image and save sequence to files (duration in number of frames)
        void getSequence(const uint_fast32_t duration);

        /// Calibrate sensor
        void calibrate(void);

        /// Name of the grabber
        const std::string& getName() const;

        /// Returns current frame
        const SensorFrame& getSensorFrame(void);

        /// Returns the current point cloud
        const PointCloud& getCloud(void) const;

        ///Closing a device
        int grabberClose();

    private:
        /// start timestamp
        std::chrono::high_resolution_clock::time_point startT;

        /// file prefix (images)
        std::string imageSeqPrefix;

        /// file prefix (depth images)
        std::string depthSeqPrefix;

        /// file prefix (point clouds)
        std::string cloudSeqPrefix;

        /// file number
        uint_fast32_t fileNo;

        ///sensor model
        XtionGrabber::UncertaintyModel asusModel;
};

#endif // FILE_GRABBER_H_INCLUDED