#ifndef __PLANNER_OMPL_H__
#define __PLANNER_OMPL_H__ 

#include "Planner.h" 
#include "ObstacleProvider.h"

#include <geometry_msgs/Point.h>
#include <fcl/collision_object.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/base/StateValidityChecker.h>

using namespace geometry_msgs;

class PlannerOMPL : public Planner
{
public:
    PlannerOMPL(const ObstacleProvider *obstProvider, 
                const MapMetaData &meta);
    ~PlannerOMPL() {}
    
    std::vector<Point> plan(const Point &start, const Point &goal); 

protected:
    class ValidityChecker :
        public ompl::base::StateValidityChecker {
    public:
        ValidityChecker(const ompl::base::SpaceInformationPtr &si,
                        const ObstacleProvider *obstProvider)
            : ompl::base::StateValidityChecker(si)
            , collider(obstProvider) {}
        /***
         * Check current state by collision with other objects
         ***/
        bool isValid(const ompl::base::State *state) const; 
    private:
        const ObstacleProvider *collider;
    };

    ompl::base::StateSpacePtr space;
    ompl::geometric::SimpleSetup ss;
};

#endif // __PLANNER_OMPL_H__
