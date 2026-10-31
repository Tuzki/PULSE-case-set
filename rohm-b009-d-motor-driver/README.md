# rohm-b009-d-motor-driver

- 原厂模型：[(B-009-D)DC-AC 3-phase 2-Level Motor Driver (Discrete)_20260525.plecs](<plecs/(B-009-D)DC-AC 3-phase 2-Level Motor Driver (Discrete)_20260525.plecs>)，SHA256 `c21f14ebc407cace25a694aa37a2deba7d27bd52d519bf55004fc5f94b48e744`。
- 原厂完整仿真区间：0–0.5 s。导出状态：**COMPLETED**。
- CSV：[waveforms_001.csv](plecs/waveforms_001.csv) · [waveforms_002.csv](plecs/waveforms_002.csv) · [waveforms_003.csv](plecs/waveforms_003.csv) · [waveforms_004.csv](plecs/waveforms_004.csv) · [waveforms_005.csv](plecs/waveforms_005.csv) · [waveforms_006.csv](plecs/waveforms_006.csv)。采样间隔 1 µs，数值以 17 位有效数字输出；按文件序号连接各段，段间没有重复行。此均匀输出网格不是 PLECS 内部积分步长，也不保证捕获所有开关边沿。
- PLECS 观测模型：[CaseSet_rohm_b009_d_motor_driver.plecs](plecs/CaseSet_rohm_b009_d_motor_driver.plecs)；仅调整观测输出，保留原厂物理和控制设置。
- PULSE：[netlist.md](pulse/netlist.md)。用户接受 20 ms 验证；未验收 0.5 s。
- PULSE 原有默认仿真声明：`.TRAN T_END=0.002 SAVE_DT=1.9999999999999999e-07`。未为本次打包修改窗口或控制逻辑。
- 原始下载资料在 `source/` 内平铺；模型运行所需器件 XML 位于 `plecs/*_plecs/`，这是 PLECS 的配套资源目录。
- 逐文件来源、哈希、导出终点和控制条件见 [provenance.json](provenance.json)。

本仓库收录输入和 PLECS 参考数据，不将 PLECS 全时长完成视为 PULSE 全时长精度通过。

## CSV 通道

| CSV 列 | 单位 | PLECS 器件路径 | 信号 |
|---|---|---|---|
| time_s | s | 仿真时间 | 时间 |
| CH001 | V | V_dc | Source voltage |
| CH002 | A | V_dc | Source current |
| CH003 | V | 3ph Meter | Measured voltage[0] |
| CH004 | V | 3ph Meter | Measured voltage[1] |
| CH005 | V | 3ph Meter | Measured voltage[2] |
| CH006 | A | 3ph Meter | Measured current[0] |
| CH007 | A | 3ph Meter | Measured current[1] |
| CH008 | A | 3ph Meter | Measured current[2] |
| CH009 | V | SiC-MOSFET_A/FET | Device voltage |
| CH010 | V | SiC-MOSFET_A1/FET | Device voltage |
| CH011 | A | SiC-MOSFET_A/FET | Device current |
| CH012 | A | SiC-MOSFET_A1/FET | Device current |
