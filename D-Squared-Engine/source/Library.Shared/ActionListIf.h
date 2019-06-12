#pragma once
#include "ActionList.h"


namespace Library
{
    class ActionListIf : public ActionList
    {

    public:

#pragma region Construction/Copy/Assignment

        ActionListIf();

        virtual ~ActionListIf() = default;

        ActionListIf(const ActionListIf& rhs) = delete;

        ActionListIf& operator=(const ActionListIf& rhs) = delete;

        ActionListIf(ActionListIf&& rhs) = delete;

        ActionListIf& operator=(ActionListIf&& rhs) = delete;

#pragma endregion

        /**
         * Executes the if statement. Runs through "then" attribute updates if condition is true, "else" attributes otherwise
         * @Param worldState: The world state object that stores the current world state
         */
        void Update(WorldState& worldState) override;

        /**
         * Mutator method for the if statement's condition
         * @Param condition: The new condition for the if statement
         */
        void SetCondition(const std::int32_t& condition);

        /**
         * Accessor method for the if statement's condition
         * @Return: The condition for the if statement
         */
        std::int32_t GetCondition() const;

        /**
         * Creates a "then" action as the consequence of the if being true
         * @Param className: The name of the class being created
         * @Param instanceName: The name of the instance of the class being created
         * @Return: A pointer to the newly instantiated action
         */
        Action* CreateThenAction(const std::string& className, const std::string& instanceName);

        /**
        * Creates an "else" action as the consequence of the if being false
        * @Param className: The name of the class being created
        * @Param instanceName: The name of the instance of the class being created
        * @Return: A pointer to the newly instantiated action
        */
        Action* CreateElseAction(const std::string& className, const std::string& instanceName);

    private:

        std::int32_t m_condition; // The condition to determine which Set of mAction will be executed

    };

    ActionFactory(ActionListIf)
}