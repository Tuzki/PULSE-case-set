# rohm-a002-d-boost-pfc

- 原厂模型：[(A-002-D) AC-DC Boost PFC Diode Rectification (Discrete)_20260525.plecs](<plecs/(A-002-D) AC-DC Boost PFC Diode Rectification (Discrete)_20260525.plecs>)，SHA256 `782b6ad109d1c8aeb55387c7786aad367f724fdae83476c674b5ca25ab9ad2a4`。
- 原厂完整仿真区间：0–0.5 s。导出状态：**COMPLETED**。
- CSV：[waveforms_001.csv](plecs/waveforms_001.csv) · [waveforms_002.csv](plecs/waveforms_002.csv) · [waveforms_003.csv](plecs/waveforms_003.csv) · [waveforms_004.csv](plecs/waveforms_004.csv) · [waveforms_005.csv](plecs/waveforms_005.csv) · [waveforms_006.csv](plecs/waveforms_006.csv)。采样间隔 1 µs，数值以 17 位有效数字输出；按文件序号连接各段，段间没有重复行。此均匀输出网格不是 PLECS 内部积分步长，也不保证捕获所有开关边沿。
- PLECS 观测模型：[CaseSet_rohm_a002_d_boost_pfc.plecs](plecs/CaseSet_rohm_a002_d_boost_pfc.plecs)；仅调整观测输出，保留原厂物理和控制设置。
- PULSE：[netlist.md](pulse/netlist.md)。历史已转换输入；验收范围见 provenance.json。
- PULSE 原有默认仿真声明：`.TRAN T_END=0.080000000 SAVE_DT=0.000001`。未为本次打包修改窗口或控制逻辑。
- 原始下载资料在 `source/` 内平铺；模型运行所需器件 XML 位于 `plecs/*_plecs/`，这是 PLECS 的配套资源目录。
- 逐文件来源、哈希、导出终点和控制条件见 [provenance.json](provenance.json)。

CSV 来自原厂控制条件。A002 的 PULSE 为既有 20 us ZOH 转换，不能把原厂连续控制 CSV 当作同模型精度基准。PULSE 默认窗口可能短于原厂全时长；收录不表示全时长 PULSE 验收。

## CSV 通道

| CSV 列 | 单位 | PLECS 器件路径 | 信号 |
|---|---|---|---|
| time_s | s | 仿真时间 | 时间 |
| CH001 | A | SiC_MOSFET/FET | Device current |
| CH002 | V | SiC_MOSFET/FET | Device voltage |
| CH003 | A | SiC_SBD/D1 | Diode current |
| CH004 | A | V_ac | Source current |
| CH005 | V | V_ac | Source voltage |
| CH006 | A | Rload | Resistor current |
| CH007 | V | Rload | Resistor voltage |
