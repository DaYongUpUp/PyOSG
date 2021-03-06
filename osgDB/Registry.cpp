// Copyright (C) 2016 Gideon May (gideon@borges.xyz)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

#include <boost/python.hpp>

#include <osg/Referenced>
#include <osgDB/Registry>

#include "held_ptr.hpp"

using namespace boost::python;

namespace {
osgDB::Registry * instance()
{
    return osgDB::Registry::instance();
}

}

namespace PyOSG {

    void init_Registry()
    {
        class_<osgDB::Registry, osg::ref_ptr<osgDB::Registry>, bases<osg::Referenced>, boost::noncopyable > 
        // class_<osgDB::Registry, osg::ref_ptr<osgDB::Registry>, boost::noncopyable > 
        registry("Registry", "Registry is a singleton factory which stores the reader/writers which are linked in at runtime for reading non-native file formats.",
            no_init);
            
        registry
            .def("readCommandLine", &osgDB::Registry::readCommandLine)
            .def("addFileExtensionAlias", &osgDB::Registry::addFileExtensionAlias)
            // .def("addDotOsgWrapper", &osgDB::Registry::addDotOsgWrapper)
            // .def("removeDotOsgWrapper", &osgDB::Registry::removeDotOsgWrapper)
            .def("addReaderWriter", &osgDB::Registry::addReaderWriter)
            .def("removeReaderWriter", &osgDB::Registry::removeReaderWriter)
            .def("loadLibrary", &osgDB::Registry::loadLibrary)
            .def("closeLibrary", &osgDB::Registry::closeLibrary)
            
            /*
            .def("getReaderWriterForExtension", &osgDB::Registry::getReaderWriterForExtension)
            .def("readObject", &osgDB::Registry::readObject)
            .def("writeObject", &osgDB::Registry::writeObject)
            .def("readImage", &osgDB::Registry::readImage)
            .def("writeImage", &osgDB::Registry::writeImage)
            .def("readNode", &osgDB::Registry::readNode)
            .def("writeNode", &osgDB::Registry::writeNode)
            */
            .def("initFilePathLists", &osgDB::Registry::initFilePathLists, 
                "initilize both the Data and Library FilePaths, by default called by the constructor, so it should only be required if you want to force the re-reading of environmental variables.")
            .def("initDataFilePathList", &osgDB::Registry::initDataFilePathList, 
                "initilize the Data FilePath by reading the OSG_FILE_PATH environmental variable.")
            .def("removeExpiredObjectsInCache", &osgDB::Registry::removeExpiredObjectsInCache)
            .def("clearObjectCache", &osgDB::Registry::clearObjectCache)
            // XXX .def("setUseObjectCacheHint", &osgDB::Registry::setUseObjectCacheHint)
            
            .def("instance", &osgDB::Registry::instance, return_value_policy<manage_osg_object>())
            .def("instance", &instance, return_value_policy<manage_osg_object>())
            .staticmethod("instance")
            ;

    }
}

