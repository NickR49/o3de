/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "EditorDefs.h"

// AzTest
#include <AzTest/AzTest.h>

// AzCore
#include <AzCore/Memory/AllocatorScope.h>

// AzFramework
#include <AzFramework/IO/LocalFileIO.h>

#include <Mocks/ICryPakMock.h>

using ::testing::NiceMock;

class EditorCoreTestEnvironment
    : public AZ::Test::ITestEnvironment
{
public:
    AZ_TEST_CLASS_ALLOCATOR(EditorCoreTestEnvironment);

    virtual ~EditorCoreTestEnvironment()
    {
    }

protected:
    void SetupEnvironment() override
    {
        m_allocatorScope.ActivateAllocators();
        m_cryPak = new NiceMock<CryPakMock>();

        // Initialize the fileIO
        AZ::IO::FileIOBase::SetInstance(&m_fileIO);

        // Setup gEnv with the systems/mocks we will be using for the unit tests
        m_stubEnv.pCryPak = m_cryPak;
        m_stubEnv.pFileIO = &m_fileIO;
        gEnv = &m_stubEnv;
    }

    void TeardownEnvironment() override
    {
        delete m_cryPak;
        m_allocatorScope.DeactivateAllocators();
    }

private:
    AZ::AllocatorScope<AZ::OSAllocator, AZ::SystemAllocator, AZ::LegacyAllocator, CryStringAllocator> m_allocatorScope;
    SSystemGlobalEnvironment m_stubEnv;
    AZ::IO::LocalFileIO m_fileIO;
    NiceMock<CryPakMock>* m_cryPak;
};

AZ_UNIT_TEST_HOOK(new EditorCoreTestEnvironment);