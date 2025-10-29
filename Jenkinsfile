pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                git branch: 'DEV', url: 'https://github.com/DouglasR99/traductor-backend.git'
            }
        }

        stage('Build') {
            steps {
                bat 'g++ src/*.cpp -o bin\\traductor.exe'
            }
        }

        stage('SonarQube Analysis') {
            environment {
                scannerHome = tool 'sonar-scanner'
            }
            steps {
                withSonarQubeEnv('sonarqube-local') {
                    bat "${scannerHome}\\bin\\sonar-scanner.bat -Dsonar.projectKey=traductor-backend -Dsonar.sources=src"
                }
            }
        }
    }
}
