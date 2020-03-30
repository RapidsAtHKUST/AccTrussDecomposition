#include "utils/ParMMapBuffer.hpp"

std::string ParMMapBuffer::folder = "/mmap/";

ParMMapBuffer::ParMMapBuffer(
  std::string path_in,
  size_t num_elems_in){
  
  num_buffers = NUM_THREADS;
  path = path_in;

  std::string dataF = path + folder + "data_head.bin";
  head = MMapBuffer::create(dataF.c_str(),num_elems_in);
  for(size_t i = 0; i < num_buffers; i++){
    dataF = path + folder + "data_" + std::to_string(i) + ".bin";
    MMapBuffer *mbuffer  = MMapBuffer::create(dataF.c_str(),num_elems_in);
    elements.push_back(mbuffer);
  }
  elements.push_back(head);
}

ParMMapBuffer::ParMMapBuffer(
  std::string path_in,
  std::vector<size_t>* num_elems_in,
  size_t num_buffers_in){
  
  num_buffers = num_buffers_in;
  path = path_in;
  std::string dataF = path + folder + "data_head.bin";
  head = MMapBuffer::create(dataF.c_str(),num_elems_in->at(0));
  for(size_t i = 0; i < num_buffers; i++){
    dataF = path + folder + "data_" + std::to_string(i) + ".bin";
    MMapBuffer *mbuffer  = MMapBuffer::create(dataF.c_str(),num_elems_in->at(i+1));
    elements.push_back(mbuffer);
  }
  elements.push_back(head);
}

uint8_t* ParMMapBuffer::get_head(const size_t tid){
  return (uint8_t*)elements.at(tid)->get_head();
}

uint8_t* ParMMapBuffer::get_address(const size_t tid){
  return (uint8_t*)elements.at(tid)->get_address();
}

size_t ParMMapBuffer::get_size(const size_t tid){
  return elements.at(tid)->getSize();
}

uint8_t* ParMMapBuffer::get_address(const size_t tid, const size_t offset){
  return (uint8_t*)elements.at(tid)->get_address(offset);
}

uint8_t* ParMMapBuffer::get_next(const size_t tid, const size_t num){
  return (uint8_t*)elements.at(tid)->get_next(num);
}

void ParMMapBuffer::roll_back(const size_t tid, const size_t num){
  elements.at(tid)->roll_back(num);
}

void ParMMapBuffer::save(){
  head->flush();
  for(size_t i = 0; i < num_buffers; i++){
    elements.at(i)->flush();
  }
}

void ParMMapBuffer::free(){
  head->discard();
  for(size_t i = 0; i < num_buffers; i++){
    elements.at(i)->discard();
  }
}