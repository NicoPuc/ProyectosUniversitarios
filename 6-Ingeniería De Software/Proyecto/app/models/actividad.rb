class Actividad < ApplicationRecord
  belongs_to :user
  has_many :requests, dependent: :destroy
  has_many :chats, dependent: :destroy
  has_many :users_participators, through: :participations, source: :user
  has_many :participations, dependent: :destroy
  has_many :activity_requests
  has_many :reviews, dependent: :destroy
  self.table_name = 'actividads'
  validates :titulo, presence: true
  validates :cantidad_personas, presence: true
  validates :precio, presence: true
  validates :fecha, presence: true  
end
