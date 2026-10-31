# PULSE-case-set

20 个 ROHM 电力电子案例的原始资料、PLECS 全时长参考 CSV，以及截至 2026-11-01 已有的最新选定 PULSE 网表。求解器独立存放于 [PULSE-solver](https://github.com/Tuzki/PULSE-solver)。

```text
<case>/
  source/          ROHM 原始 ZIP、PDF、PLECS 和已有 XML，文件平铺
  plecs/           未修改的原厂 PLECS、观测副本、全时长 CSV
    *_plecs/       PLECS 必需的器件资源，保持其原有查找结构
  pulse/           netlist.md、所需 C 源和头文件；缺失案例明确标注
  README.md        文件说明、通道与限制
  provenance.json 来源、SHA256、模型条件、实际导出范围
```

## 案例目录

完整时长是原厂模型的 `Test_time`，不是之前精度验证的短窗口。所有本次完成的 CSV 均由 PLECS 4.8.2 新执行导出；1 µs 均匀输出网格，包含 t=0 和最终终点。CSV 每段最多 100000 行，以避免超过 GitHub 单文件大小限制。按编号拼接即可恢复全时段；没有插值补齐失败结果。

| case | 原厂时长 / s | 全时长 CSV | 数据行数 | PULSE 网表 | PULSE 既有状态 / 范围 |
|---|---:|---|---:|---|---|
| [A-002-D](rohm-a002-d-boost-pfc/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [A-010-DOT](rohm-a010-dot-totem-pole-pfc-sync/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 初步验证通过；0.5 s 结果留有门极边界差异 |
| [A-011-D](rohm-a011-d-totem-pole-pfc-diode/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [A-021-D](rohm-a021-d-vienna-pfc/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [A-021-DOT](rohm-a021-dot-vienna-pfc/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [B-004-D](rohm-b004-d-single-phase-inverter/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [B-004-DOT](rohm-b004-dot-single-phase-inverter/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [B-009-D](rohm-b009-d-motor-driver/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 用户接受 20 ms 验证；未验收 0.5 s |
| [B-011-DOT](rohm-b011-dot-npc-t-inverter/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 候选；INITIAL_MODE_CYCLE，未跑通整机 |
| [B-012-DOT](rohm-b012-dot-npc-i-inverter/README.md) | 0.5 | COMPLETED | 500,001 | 已收录 | 原 C 候选；门极边界语义待查；不采用 DSH 提前关断版本 |
| [C-002-D](rohm-c002-d-boost/README.md) | 0.3 | COMPLETED | 300,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [C-006-D](rohm-c006-d-buck/README.md) | 0.3 | COMPLETED | 300,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [C-010-D](rohm-c010-d-flyback/README.md) | 0.3 | COMPLETED | 300,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [C-011-D](rohm-c011-d-forward/README.md) | 0.4 | COMPLETED | 400,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [C-012-D](rohm-c012-d-llc-half-bridge/README.md) | 0.3 | COMPLETED | 300,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [C-012-DOT](rohm-c012-dot-llc-half-bridge/README.md) | 0.3 | COMPLETED | 300,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [C-014-D](rohm-c014-d-llc-full-bridge/README.md) | 0.2 | COMPLETED | 200,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [C-014-DOT](rohm-c014-dot-llc-full-bridge/README.md) | 0.2 | COMPLETED | 200,001 | 已收录 | 历史已转换输入；验收范围见 provenance.json |
| [C-019-D](rohm-c019-d-phase-shift-full-bridge/README.md) | 0.2 | COMPLETED | 200,001 | 已收录 | 最新等价表达候选；约 100 ns 首次整流换流后失败，未通过 |
| [C-019-DOT](rohm-c019-dot-phase-shift-full-bridge/README.md) | 0.15 | COMPLETED | 150,001 | **尚无网表** | 尚无已转换网表；未拿 D 版冒充 DOT 版 |

## 模型条件与使用

- 原厂 `.plecs` 按原始字节保留，可在 PLECS 中直接打开运行；旁边的 `CaseSet_*.plecs` 为 CSV 采集所用观测副本。副本仅调整测量输出及模型名称；多数副本把仿真时长表达式展开为原厂相同数值。
- A021-D 通过原有 Scope 信号与既有电流探针导出，保留 14 个电气通道及原 Scope 的 4 个温度通道。其余 19 例添加独立观测输出。原厂电气与控制组件、参数、初值不变，观测差异见各例 provenance.json。
- CSV 记录原厂模型的电气观测通道；A021-D 还保留上述温度通道。通道路径和单位在各 case 的 README 中逐列列明。没有把历史的十点、2 ms、20 ms 或稳态窗口冒充原厂全时段。
- A002 的既有 PULSE 网表包含 20 µs ZOH，原厂 PLECS 为连续控制。因此该 CSV 是原厂参考，不能直接宣称是相同控制条件的精度基准。其他输入的短窗口、候选失败、边界差异也保留说明。
- PULSE 网表和控制源按现有选定版本原样复制；默认 `.TRAN` 可能短于原厂仿真时长。未重新运行 PULSE，未更改求解器或网表以取得通过。
- C019-DOT 之前尚未转换，没有对应网表；`pulse/README.md` 明确保留缺口。C019-D、B011 等失败候选的存在不表示它们已通过验证。
- C 控制器依赖 PULSE 求解器提供的 `pulse/software.h`。未上传本机编译缓存、DLL 或 EXE。

原始资料来源：[ROHM PLECS Circuit](https://www.rohm.com/support/plecs-circuit)。ROHM 原厂资料的权利归其权利人，本仓库没有为第三方资料另行授予许可。各模型及原始 ZIP 内的说明保持原样。
