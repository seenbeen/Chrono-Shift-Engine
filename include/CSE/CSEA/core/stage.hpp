#ifndef CSEA_CORE_STAGE_HPP
#define CSEA_CORE_STAGE_HPP

namespace CSEA { namespace Core {
    class Stage {
        friend class Engine;
    protected:
        virtual void onLoad() = 0;
        virtual void onUnload() = 0;
        virtual void onTransitionOutOf() = 0;
        virtual void onTransitionInto() = 0;
        virtual void onUpdate() = 0;
    public:
        /*
            These should NOT be used on engine specific things.
            All Loading must be done in the onLoad and onUnload function hooks,
            otherwise you may get stuff liek funky "null pointer" inconsistencies.
        */
        Stage();
        virtual ~Stage();
    };
}}
#endif
