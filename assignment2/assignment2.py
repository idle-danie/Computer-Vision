# Computer Vision assignment2
## 201821053 Kim Hyung Jun

import cv2
import numpy as np

def identify_circles(src): # 원(코인)의 개수와 원 식별 영상 반환
    grey = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY) # 흑백영상 만들기
    blur = cv2.GaussianBlur(grey, (9, 9), 3) # 가우시안 블러로 노이즈 제거    
    
    circles = cv2.HoughCircles(blur, cv2.HOUGH_GRADIENT, 1.3, 60, param1=90, param2=40, minRadius=40, maxRadius=120)
    # HoughCircles(image, method(검출방법), dp(해상도)), minDist(검출한 원의 중심과의 최소거리), param1(high threshold), param2(low threshold), minRadius, maxRadius)
    
    count = 0 # 원(코인)의 개수
    dst = src.copy() # 기존 영상 위에 새로운 원을 입히기 위해 카피본 생성
    for i in range(circles.shape[1]): # 검출된 원만큼 반복
        cx, cy, radius = circles[0][i] # 원의 중심 좌표와 반지름 
        cv2.circle(dst, (int(cx), int(cy)), int(radius), (0, 0, 255), 2, cv2.LINE_AA) # 원 그리기       
        count+=1 # 원의 개수 추가 +1
    return dst, count # 새로운 영상과 원의 개수 반환

src0 = cv2.imread('coins0.jpg')
src1 = cv2.imread('coins1.jpg')
src2 = cv2.imread('coins2.jpg')
src3 = cv2.imread('coins3.jpg')
src4 = cv2.imread('coins4.jpg')
src5 = cv2.imread('coins5.jpg')

dst0, count0 = identify_circles(src0)
dst1, count1 = identify_circles(src1)
dst2, count2 = identify_circles(src2)
dst3, count3 = identify_circles(src3)
dst4, count4 = identify_circles(src4)
dst5, count5 = identify_circles(src5)

cv2.imshow('dst0: ' + str(count0) + 'coins', dst0)
cv2.imshow('dst1: ' + str(count1) + 'coins', dst1)
cv2.imshow('dst2: ' + str(count2) + 'coins', dst2)
cv2.imshow('dst3: ' + str(count3) + 'coins', dst3)
cv2.imshow('dst4: ' + str(count4) + 'coins', dst4)
cv2.imshow('dst5: ' + str(count5) + 'coins', dst5)

cv2.waitKey(0)
cv2.destroyAllWindows()