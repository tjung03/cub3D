# cub3D

2차원 격자 맵을 1인칭 화면으로 그리는 C 기반 Raycasting 프로젝트입니다. 플레이어 위치와 시선 방향으로 벽까지의 거리를 계산하고, 그 거리에 맞춰 벽과 맵 안의 물체를 화면에 그립니다.

2021년 42 Seoul 과제로 작성했습니다. **격자 단위의 벽 탐색, 벽 표면 이미지의 좌표 계산, 벽과 물체의 앞뒤 관계를 반영한 렌더링**이 핵심 구현입니다.

맵 안의 물체는 2D 이미지인 스프라이트(sprite)로 표현합니다. 물체를 먼 순서부터 그리고 벽까지의 거리와 비교해, 벽 뒤에 있는 부분은 화면에 그리지 않습니다.

## 구현 기능

| 기본 버전 | 보너스 버전에서 추가 |
| --- | --- |
| 방향별 벽 텍스처, 바닥·천장 색상 | 두 종류의 스프라이트 |
| 이동·회전, 벽·물체를 통과하지 않도록 이동 제한 | 마우스 위치에 따른 시점 회전 |
| 물체의 거리 정렬과 벽 뒤 영역 표시 제외 | 플레이어 위치·방향을 표시하는 미니맵 |
| 첫 화면을 BMP 파일로 저장 | 시간 제한 막대와 배경음 재생 |

## 코드 구조

| 경로 | 역할 |
| --- | --- |
| [main.c](main.c) · [cub3d.c](cub3d.c) | 인자 검사, 게임 상태·창·이벤트 루프 초기화 |
| [parse.c](parse.c) · [parse_tools.c](parse_tools.c) · [parse_check.c](parse_check.c) | 해상도·텍스처·색상·맵과 플레이어 정보 읽기 |
| [raycasting.c](raycasting.c) · [engine.c](engine.c) | 격자 단위 벽 탐색, 벽 높이와 텍스처 좌표 계산 |
| [sprite.c](sprite.c) · [sprite_details.c](sprite_details.c) | 스프라이트 정렬·투영·깊이 비교 |
| [draw.c](draw.c) · [key.c](key.c) | 이미지 버퍼 출력, 이동과 회전 |
| [bitmap.c](bitmap.c) | BMP 헤더와 픽셀 데이터 저장 |
| [bonus/](bonus/) | 보너스 버전의 별도 소스·맵·텍스처 |
| [mlx/](mlx/) | 함께 포함된 macOS용 MiniLibX |
| [maps/](maps/) · [textures/](textures/) | 기본 예제 맵과 64×64 XPM 텍스처 |

## 렌더링 흐름

1. **광선 생성:** 플레이어 방향과 카메라 평면으로 화면 열마다 광선 방향을 계산합니다.
2. **벽 탐색:** DDA(Digital Differential Analyzer) 방식으로 광선이 지나는 격자를 차례로 검사해 벽 `1`을 찾습니다. 시선 방향 기준의 깊이로 화면에 그릴 벽 높이를 계산합니다.
3. **텍스처 합성:** 충돌 면과 방향에 따라 동·서·남·북 텍스처를 선택하고 버퍼를 채웁니다.
4. **물체 그리기:** 물체의 위치와 크기를 화면 좌표로 변환합니다. 먼 물체부터 그리되, 같은 화면 열의 벽보다 앞에 있는 부분만 버퍼에 덧그립니다.
5. **화면 표시:** 완성한 버퍼를 MiniLibX 이미지로 옮겨 창에 출력합니다.

오브젝트 표시 오류를 수정하는 과정에서 [벽과 물체를 2차원 색상 버퍼에 모은 뒤 한 번에 출력하는 방식](https://github.com/tjung03/cub3D/commit/c7b744e4024de39ba64b6bcad390a99d8037d893)을 적용했습니다. 벽에 가까이 갔을 때 텍스처가 휘던 문제는 [그리기 시작 위치를 화면 범위로 제한](https://github.com/tjung03/cub3D/commit/ae4125058f928b3281a863b6acc8724c202749b0)하는 수정으로 다뤘습니다.

## macOS 빌드와 실행

C 컴파일러, Make, Swift 컴파일러와 macOS SDK가 필요합니다. 저장소 루트에서 포함된 MiniLibX를 먼저 빌드합니다.

```bash
make -B -C mlx
make
DYLD_LIBRARY_PATH="$PWD/mlx" ./cub3D maps/cub3d.cub
```

보너스 버전은 다음과 같이 실행합니다.

```bash
make b_all
DYLD_LIBRARY_PATH="$PWD/mlx" ./cub3D_bonus bonus/maps_bonus/cub3d_bonus.cub
```

맵의 텍스처·음원 경로가 저장소 루트 기준이므로 같은 위치에서 실행합니다. 보너스 배경음은 macOS의 `afplay`로 재생하며, 보너스 종료 코드는 실행 중인 모든 `afplay` 프로세스를 종료합니다.

| 입력 | 동작 |
| --- | --- |
| W / S | 전진 / 후진 |
| A / D | 좌우 이동 |
| ← / → | 시점 회전 |
| 마우스 | 보너스에서 화면 내 위치에 따라 시점 회전 |
| Esc / 창 닫기 | 종료 |

## 맵과 텍스처

기본 `.cub` 파일은 `R` 해상도, `NO/SO/WE/EA` 벽 텍스처, `S` 스프라이트, `F/C` 바닥·천장 RGB 색상과 격자 맵으로 구성됩니다. [기본 맵](maps/cub3d.cub)과 [보너스 맵](bonus/maps_bonus/cub3d_bonus.cub)을 기준으로 수정할 수 있습니다.

- `1`: 벽, `0`: 빈 공간, `2`: 스프라이트
- `N/S/E/W`: 플레이어 시작 위치와 방향. 한 곳만 지정합니다.
- 보너스는 `SS` 텍스처와 격자 값 `3`으로 두 번째 스프라이트를 지정합니다.
- 텍스처는 64×64 XPM입니다. 맵은 벽으로 둘러싸인 형태로 작성합니다.
- 바닥·천장의 `0,0,0`은 현재 검사 코드에서 색상 오류로 처리됩니다.

미니맵은 화면 높이가 720 이상일 때 표시됩니다. 보너스의 제한 시간은 기본 88초이며, 높이가 88보다 작은 화면에서는 `화면 높이 - 1`초로 줄어듭니다.

## BMP 저장

`--save`는 시작 위치에서 그린 화면을 파일로 저장합니다.

```bash
DYLD_LIBRARY_PATH="$PWD/mlx" ./cub3D maps/cub3d.cub --save
DYLD_LIBRARY_PATH="$PWD/mlx" ./cub3D_bonus bonus/maps_bonus/cub3d_bonus.cub --save
```

각각 `bitmap.bmp`, `bitmap_bonus.bmp`를 생성합니다. `make clean`과 `make b_clean`은 해당 BMP도 삭제합니다.

## 그래픽 환경

게임의 거리 계산과 픽셀 합성은 C 코드가 수행하며, 포함된 MiniLibX는 Swift·Cocoa·Metal을 사용합니다. 루트 Makefile에는 OpenGL·AppKit 프레임워크 링크 옵션도 남아 있습니다.

OpenGL은 macOS 10.14에서 deprecated 되었고 Apple은 Metal을 안내합니다. [Apple 그래픽 문서](https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_pg_concepts/opengl_pg_concepts.html)
