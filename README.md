# This is to help addressing problems in https://github.com/GENIE-MC/Generator/issues/226

## Compiling the tool 
```
mkdir build && cd build && cmake .. && make -j$(nproc)
```
This might need a modern version of GCC and CERN ROOT, and also you need https://github.com/nlohmann/json to compile this

## Generate $\frac{\mathrm{d} \sigma}{\mathrm{d} T_{K^+}}$ plots

For **every** set of GENIE outputs, write a analysis configuration file

```json
{
    "output_path": "/path/to/output/G18_10b_02_11b.root",
    "input_file_list": [
      "path/to/output1.root",
      ...
      "path/to/outputN.root"
    ],
    "spline_file": "/path/to/spline/file.root",
    "spline_path": "nu_mu_C12/tot_cc"
}
```

Then run the analysis tool
  
```
/path/to/build/genie_kaon /path/to/config/file.json
```

For each batch of GENIE simulation. 

## Plotting the results

Write another configuration file to do the plot:

```json
{
    "plot_title": "Proton Momentum; #it{T}_{K} (GeV); d#it{#sigma}/d#it{T}_{K} (cm^{2}/GeV/nucleon)",
    "max_x_value": 0.5,
    "output_names": [
        "plots/kaonE.eps",
        "plots/kaonE.png",
        "plots/kaonE.pdf"
    ],
    "hists": [
        {
            "legend": "atmo",
            "file_path": "atmo/genie/G18_10b_02_11b.root",
            "hist": "kaonE",
            "rebin": 4,
            "line_color": 1
        },
        {
            "legend": "mixed",
            "file_path": "new/genie/G18_10b_02_11b.root",
            "hist": "kaonE",
            "rebin": 4,
            "line_color": 600
        },
        {
            "legend": "plain, with aligned edge",
            "file_path": "plain_aligned/genie/G18_10b_02_11b.root",
            "hist": "kaonE",
            "rebin": 4,
            "line_color": 880
        }
    ],
    "legend_place": {
        "x1": 0.3,
        "y1": 0.15,
        "x2": 0.9,
        "y2": 0.4
    },
    "legend_columns": 1,
    "legend_header": "E^{-2.7} #nu_{#mu}CC on carbon ",
    "logy": false
}
```

Then run the plotting tool
```
/path/to/build/merge_plot /path/to/config/file.json
```

Then you can get plot at path specified in the configuration file's `output_names` part.

The plotted variable is specified in `"hist"` entries. You can change to `kaonE_cut` to see plotts with only $1~\mathrm{GeV} < E_{\nu} < 10~\mathrm{GeV}$

## Definition of Y axis

If you run the code as it is, it is $\frac{\mathrm{d} \sigma}{\mathrm{d} T_{K^+}}$ for leading $K^{+}$.

You can change code as a comment in `genie_kaon.cxx` $\frac{m\mathrm{d} \sigma}{\mathrm{d} T_{K^-}}$, where $m$ if for $K^{+}$ multiplicity.
