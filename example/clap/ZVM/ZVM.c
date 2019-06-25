// Sunday, April 07, 2019

#include <jtk/clap/ClapConfiguration.h>

jtk_Array_t* createArguments(uint8_t** vector, int32_t size) {
    return jtk_Array_migrate_v(vector + 1, size, (jtk_Array_MigrateFunction_t)jtk_String_new);
}

/*******************************************************************************
 * VirtualMachineDriver                                                        *
 *******************************************************************************/

struct zen_VirtualMachineDriver_t {
    jtk_ClapConfiguration_t* m_configuration;
    jtk_Array_t* m_arguments;
};

#define JTK_PARAMETER_IDENTIFIER_ENTITY_PATH        1000
#define JTK_PARAMETER_IDENTIFIER_TEST               1100
#define JTK_PARAMETER_IDENTIFIER_VALIDATE           1200
#define JTK_PARAMETER_IDENTIFIER_DEFINE             1300
#define JTK_PARAMETER_IDENTIFIER_HELP               2000
#define JTK_PARAMETER_IDENTIFIER_LOG                2100
#define JTK_PARAMETER_IDENTIFIER_VERSION            2200
#define JTK_PARAMETER_IDENTIFIER_MAIN_CLASS         3000

void zen_VirtualMachineDriver_handleResult(jtk_Parameter_t* parameter, void* result) {
    int32_t identifier = jtk_Parameter_getIdentifier(parameter);
    
    switch (identifier) {
        case JTK_PARAMETER_IDENTIFIER_HELP: {
            printf("Help!\n");
            break;
        }
    }
}

void zen_VirtualMachineDriver_configureClap(zen_VirtualMachineDriver_t* driver) {
    jtk_ClapConfiguration_t* configuration = driver->m_clapConfiguration;

    jtk_Parameter_t* helpParameter = jtk_Parameter_new(JTK_PARAMETER_IDENTIFIER_HELP, "Help", "Prints the help message.", "help", "h");
    jtk_Parameter_t* mainClassParameter = jtk_Parameter_newWildcard(JTK_PARAMETER_IDENTIFIER_MAIN_CLASS, "Main Class", "The class that implements the main function.", JTK_CONSUMPTION_MODE_GREEDY);

    jtk_ClapConfiguration_addParameters(configuration, 2, helpParameter, mainClassParameter);
    jtk_ClapConfiguration_setResultHandler(configuration, zen_VirtualMachineDriver_handleResult, driver);
}

zen_VirtualMachineDriver_t* zen_VirtualMachineDriver_new(uint8_t** arguments, int32_t size) {
    zen_VirtualMachineDriver_t* driver = jtk_Memory_allocate(zen_VirtualMachineDriver_t, 1);
    driver->m_arguments = zen_VirtualMachineDriver_createArguments(arguments, size);
    driver->m_clapConfiguration = jtk_ClapConfiguration_new();

    zen_VirtualMachineDriver_configureClap(driver);

    return driver;
}

void zen_VirtualMachineDriver_delete(zen_VirtualMachineDriver_t* driver) {
    jtk_Assert_assertObject(driver, "The specified virtual machine driver is null.");

    jtk_ClapConfiguration_delete(driver->m_clapConfiguration);
    jtk_Array_delete(driver->m_arguments);
    jtk_Memory_deallocate(driver);
}

int32_t main(int32_t size, char** arguments) {
    zen_VirtualMachineDriver_t* driver = zen_VirtualMachineDriver_new(arguments, size);
    zen_VirtualMachineDriver_drive(driver);
    jtk_VirtualMachineDriver_delete(driver);

    return 0;
}