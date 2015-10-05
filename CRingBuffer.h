#ifndef CRINGBUFFER_H
#define CRINGBUFFER_H


class CRingBuffer
{
public:
    explicit CRingBuffer(int bufferSize);
    ~CRingBuffer();

    void push_back(const float& digit);
    float pop_front();

private:
    bool read(float& digit);
    bool write(const float& digit);

    unsigned long m_readAbsolutePosition;
    unsigned long m_writeAbsolutePosition;
    const unsigned int m_bufferSize;
    float* m_pBuffer;
};

#endif // CRINGBUFFER_H
