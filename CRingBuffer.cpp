#include "CRingBuffer.h"

CRingBuffer::CRingBuffer(int bufferSize)
    : m_readAbsolutePosition(0)
    , m_writeAbsolutePosition(0)
    , m_bufferSize(bufferSize)
    , m_pBuffer(new float[m_bufferSize])
{
}

CRingBuffer::~CRingBuffer()
{
    delete [] m_pBuffer;
}

void CRingBuffer::push_back(const float& digit)
{
    while (!write(digit)) {}
}

bool CRingBuffer::read(float& digit)
{
    const unsigned int writePos = m_writeAbsolutePosition % m_bufferSize;
    const unsigned int readPos = m_readAbsolutePosition % m_bufferSize;

    bool canRead = false;
    if (writePos == readPos)
    {
        canRead = (m_writeAbsolutePosition - m_readAbsolutePosition > 0);
    }
    else
    {
        canRead = true;
    }

    if (canRead)
    {
        digit = m_pBuffer[readPos];
        m_readAbsolutePosition += 1;
    }
    return canRead;
}

bool CRingBuffer::write(const float& digit)
{
    const unsigned int writePos = m_writeAbsolutePosition % m_bufferSize;
    const unsigned int readPos = m_readAbsolutePosition % m_bufferSize;
    bool canWrite = false;
    if (writePos == readPos)
    {
        canWrite = (m_bufferSize - m_writeAbsolutePosition + m_readAbsolutePosition > 0);
    }
    else
    {
        canWrite = true;
    }
    if (canWrite)
    {
        m_pBuffer[writePos] = digit;
        m_writeAbsolutePosition += 1;
    }
    return canWrite;
}
