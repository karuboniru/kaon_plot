#pragma once
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TObjString.h>
#include <TSpline.h>
#include <event.h>
#include <memory>
#include <string>
#include <vector>

void make_pie_plot(std::vector<std::pair<std::string, double>> data,
                   std::string filename);

template <typename T, typename U> void save(T &&t, U &&u) {
  for (auto &&tt : t) {
    tt->SetDirectory(&*u);
  }
  u->Write();
  for (auto &&tt : t) {
    tt->SetDirectory(0);
  }
}

event::channel getmode_nuwro(TObjString &code);

event::channel get_mode_genie(const TObjString &code);

template <typename T>
std::unique_ptr<T> get_object(std::string file_path, std::string obj_path) {
  TFile root_file{file_path.c_str(), "READ"};
  auto objptr = static_cast<T *>(root_file.Get(obj_path.c_str())->Clone());
  assert(objptr);
  return std::unique_ptr<T>{objptr};
}

std::pair<double, double> get_xsec(TH1 *h_rate, TGraph *spline);


