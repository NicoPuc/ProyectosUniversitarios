class User < ApplicationRecord
  attr_accessor :updating_password
  has_many :participations, dependent: :destroy
  has_many :requests, dependent: :destroy
  has_many :actividads, dependent: :destroy
  has_many :participated_actividads, through: :participations, source: :actividad
  has_many :reviews, dependent: :destroy
  has_one :admin
  has_many :initiated_chats, foreign_key: :user1_id, class_name: 'Chat', dependent: :destroy
  has_many :received_chats, foreign_key: :user2_id, class_name: 'Chat', dependent: :destroy
  has_many :messages, dependent: :destroy
  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable, :trackable and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :validatable
  
  # Validaciones de longitud minima para la contrasena y nombre de usuario
  validates :password, presence: true, if: :updating_password, length: { minimum: 10 }
  validates :name, presence: true, length: { minimum: 10 }
  validates :phone, presence: true
    
  # Validacion del formato del correo electronico
  validates :email, presence: true, format: { with: URI::MailTo::EMAIL_REGEXP }
end
