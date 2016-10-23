/*
 * Copyright (c) 2016, Kentaro Wada.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Kentaro Wada. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RVIZ_IMAGE_CONVERSION_H
#define RVIZ_IMAGE_CONVERSION_H

#include <QImage>

#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

namespace enc = sensor_msgs::image_encodings;

namespace rviz
{

QImage rosMsgToQImage(const sensor_msgs::Image& msg)
{
  if (msg.encoding == enc::MONO8)
  {
    return QImage(msg.data.data(), msg.width, msg.height, msg.step, QImage::Format_Mono);
  }
  else if (msg.encoding == enc::RGB8)
  {
    return QImage(msg.data.data(), msg.width, msg.height, msg.step, QImage::Format_RGB888);
  }
  else if (msg.encoding == enc::BGR8)
  {
    return QImage(msg.data.data(), msg.width, msg.height, msg.step, QImage::Format_RGB888).rgbSwapped();
  }
  else
  {
    throw std::runtime_error("Unsupported encoding to convert ROSMsg to QImage.");
  }
}

QImage rosMsgToQImage(const sensor_msgs::ImageConstPtr& msg)
{
  rosMsgToQImage(*msg);
}

void qImageToRosMsg(const QImage& qimage, sensor_msgs::Image& msg)
{
  if (qimage.format() == QImage::Format_Mono)
  {
    sensor_msgs::fillImage(msg, enc::MONO8, qimage.height(), qimage.width(),
                           qimage.bytesPerLine(), qimage.bits());
  }
  else if (qimage.format() == QImage::Format_RGB888)
  {
    sensor_msgs::fillImage(msg, enc::RGB8, qimage.height(), qimage.width(),
                           qimage.bytesPerLine(), qimage.bits());
  }
  else
  {
    throw std::runtime_error("Unsupported encoding to convert QImage to ROSMsg.");
  }
}

}  // namespace rviz

#endif  // RVIZ_IMAGE_CONVERSION_H
