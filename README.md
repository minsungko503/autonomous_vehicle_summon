# 지하주차장을 위한 D* 알고리즘 기반 자율 차량 호출 시스템

![ICROS 2025](https://img.shields.io/badge/ICROS-2025-blue)

## 개요

본 프로젝트는 GPS 음영 지역인 지하주차장에서 사용자 편의성을 증대시키기 위한 자율 차량 호출 시스템을 구현합니다. 카메라 기반 실시간 차선 인식과 라이다 SLAM 기반의 고정밀 지도 정보를 활용하여, 사용자의 호출에 따라 D* 알고리즘을 통해 최적 경로를 계획하고 지하주차장 출구까지 자율적으로 이동합니다.

이 시스템은 2025년 제40회 제어로봇시스템학회 학술대회(ICROS 2025)에서 발표될 예정입니다.

## 핵심 기능

- **QR 코드 기반 맵 인식**: 주차장 진입 시 QR코드를 통해 주차장 맵 정보 획득
- **D* 알고리즘 기반 경로 계획**: 동적 환경에서의 효율적 재계획 지원
- **LQR 기반 경로 추종 제어**: 5cm 이내의 경로 추종 정확도 달성

## 시스템 구성

### 하드웨어 구성
- **임베디드 보드**: Jetson Orin Nano
- **차량 플랫폼**: Traxxas SLASH 4x4 VXL (1/10 스케일)
- **센서**:
  - 180° 시야각 어안 렌즈 USB 카메라
  - HOKUYO UST-10LX 라이다 센서
- **제어장치**: VESC 6 MkVI 모터 제어 장치
- **전원**: LiPo (5000mAh, 40C, 11.1V) 배터리

### 소프트웨어 구성
- **운영체제**: Ubuntu 20.04
- **미들웨어**: ROS Noetic
- **위치추정**: EKF(Extended Kalman Filter) + AMCL(Adaptive Monte Carlo Localization)
- **맵핑**: Cartographer SLAM
- **경로계획**: D* 알고리즘
- **제어**: LQR(Linear Quadratic Regulator) 제어기

## 테스트 환경

1/10 스케일의 축소 주차장 테스트베드(3.5m × 4.3m)를 구축하여 실험을 진행하였으며, 실제 지하주차장의 주차 공간 및 통로를 모사하였습니다.

## 설치 방법

```bash
# 1. 저장소 클론
cd ~/catkin_ws/src
git clone https://github.com/patrick-kook/Capstone-Design.git

# 2. 의존성 패키지 설치
sudo apt-get update
sudo apt-get install ros-noetic-tf2-sensor-msgs ros-noetic-navigation ros-noetic-robot-localization

# 3. 캐킨 워크스페이스 빌드
cd ~/catkin_ws
catkin_make

# 4. 환경 설정
source ~/catkin_ws/devel/setup.bash
```

## 실행 방법

```bash

roslaunch sim_env move_base.launch

```

## 프로젝트 구조

```
Capstone-Design/
├── core/                          # 핵심 알고리즘 및 기능
│   ├── common/                    # 공통 유틸리티 모듈
│   │   ├── include/               # 헤더 파일
│   │   ├── src/                   # 소스 파일
│   │   ├── CMakeLists.txt         # 빌드 설정
│   │   └── package.xml            # 패키지 정보
│   ├── controller/                # 제어 알고리즘
│   │   ├── config/                # 제어기 설정 파일
│   │   ├── controller/            # 기본 제어기
│   │   └── lqr_controller/        # LQR 제어기 구현
│   └── path_planner/              # 경로 계획 알고리즘
│       ├── config/                # 경로 계획 설정
│       └── path_planner/          # 경로 계획 구현
│           ├── include/           # 헤더 파일
│           ├── src/               # 소스 파일
│           │   ├── graph_planner/ # 그래프 기반 경로 계획
│           │   │   ├── astar_planner.cpp    # A* 알고리즘
│           │   │   ├── dstar_planner.cpp    # D* 알고리즘
│           │   │   └── voronoi_planner.cpp  # Voronoi 다이어그램 기반 계획
│           │   ├── utils/         # 유틸리티 함수
│           │   ├── path_planner.cpp        # 경로 계획 기본 클래스
│           │   └── path_planner_node.cpp   # ROS 노드 구현
│           ├── CMakeLists.txt     # 빌드 설정
│           ├── package.xml        # 패키지 정보
│           └── path_planner_plugin.xml     # 플러그인 정의
├── plugins/                       # 플러그인
│   └── map_plugins/               # 맵 관련 플러그인
├── sim_env/                       # 시뮬레이션 환경
│   ├── launch/                    # 실행 파일
│   │   └── move_base.launch       # 경로 계획 및 제어 실행 파일
│   ├── CMakeLists.txt             # 빌드 설정
│   └── package.xml                # 패키지 정보
└── README.md                      # 프로젝트 설명서
```

## 논문 정보

본 프로젝트는 2025년 제40회 제어로봇시스템학회 학술대회(ICROS 2025)에서 다음 논문으로 발표됩니다:

"지하주차장 환경에서의 D* 알고리즘 기반 자율 차량 호출 시스템"  

국민대학교 자동차공학과 :
고민성, 김재헌   

자동차IT융합학과 : 
손현수, 안지혁

국민대학교 자동차공학과 (E-mail: {koms4321, wjeheheh}@kookmin.ac.kr)
국민대학교 자동차IT융합학과 (E-mail: {gustn28999, jhahn2011}@kookmin.ac.kr)
